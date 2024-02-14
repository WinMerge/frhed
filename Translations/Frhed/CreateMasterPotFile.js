////
// This script creates the master POT file (en-US.pot).
//
// Copyright (C) 2007 by Tim Gerundt
// Released under the "GNU General Public License"

var ForReading = 1;

var NO_BLOCK = 0;
var MENU_BLOCK = 1;
var DIALOGEX_BLOCK = 2;
var STRINGTABLE_BLOCK = 3;
var VERSIONINFO_BLOCK = 4;
var ACCELERATORS_BLOCK = 5;
var TEXTINCLUDE_BLOCK = 6;
var BITMAP_BLOCK = 7;

var oFSO = new ActiveXObject("Scripting.FileSystemObject");

var bRunFromCmd = false;
if (oFSO.GetFileName(WScript.FullName).toLowerCase() === "cscript.exe") {
  bRunFromCmd = true;
}

Main();

////
// ...
function Main() {
  var StartTime = new Date().getTime();
  
  InfoBox("Creating POT file from heksedit.rc...", 3);
  
  var bNecessary = true;
  if (oFSO.FileExists("en-US.pot") && oFSO.FileExists("heksedit.rc")) { //If the POT and RC file exists...
    bNecessary = GetArchiveBit("../../Frhed/heksedit.rc") || GetArchiveBit("en-US.pot") || GetArchiveBit("heksedit.rc"); //RCs or POT file changed?
  }
  
  if (bNecessary) { //If update necessary...
    var oStrings = GetStringsFromRcFile("../../Frhed/heksedit.rc");
    CreateMasterPotFile("en-US.pot", oStrings);
    SetArchiveBit("../../Frhed/heksedit.rc", false);
    SetArchiveBit("en-US.pot", false);
    SetArchiveBit("heksedit.rc", false);
    for (var it = new Enumerator(oFSO.GetFolder(".").Files); !it.atEnd(); it.moveNext()) { //For all files in the current folder...
      var oFile = it.item();
      if (oFSO.GetExtensionName(oFile.Name).toLowerCase() === "po") { //If a PO file...
        SetArchiveBit(oFile.Path, true);
      }
    }
    
    var EndTime = new Date().getTime();
    var Seconds = (EndTime - StartTime) / 1000.0;
    
    InfoBox("POT file created, after " + Seconds + " second(s).", 10);
  } else { //If update NOT necessary...
    InfoBox("POT file already up-to-date.", 10);
  }
}

function replacei(text, find, replace, ignorecase) {
  if (!ignorecase)
    return text.split(find).join(replace);
  var textLower = text.toLowerCase();
  var findLower = find.toLowerCase();
  var pos = textLower.length;
  while (pos >= 0 && (pos = textLower.lastIndexOf(findLower, pos)) >= 0) {
    text = text.substr(0, pos) + replace + text.substr(pos + findLower.length);
    pos--;
  }
  return text;
}

////
// ...
function GetStringsFromRcFile(sRcFilePath) {
  var fContinuation = false;
  var oBlacklist = GetStringBlacklist("StringBlacklist.txt");
  var oStrings = {};
  if (oFSO.FileExists(sRcFilePath)) { //If the RC file exists...
    var sRcFileName = oFSO.GetFileName(sRcFilePath);
    var iLine = 0;
    var iBlockType = NO_BLOCK;
    var oRcFile = oFSO.OpenTextFile(sRcFilePath, ForReading);
    var oLcFile = oFSO.CreateTextFile("heksedit.rc", true);
    while (!oRcFile.AtEndOfStream) { //For all lines...
      var sLcLine = oRcFile.ReadLine();
      var sLine = sLcLine.replace(/^\s+|\s+$/g, "");
      sLine = sLine.replace(/\t/g, " ");
      iLine++;
      
      var sReference = sRcFileName + ":" + iLine;
      var sString = "";
      var sComment = "";
      var sContext = "";
      
      if (fContinuation) {
        // Nothing to do
      } else if (sLine.substring(0, 2) === "//") { //If comment line...
        sLine = "";
        //IGNORE FOR SPEEDUP!
      } else if (sLine.indexOf(" TEXTINCLUDE") >= 0) { //TEXTINCLUDE...
        iBlockType = TEXTINCLUDE_BLOCK
      } else if (sLine.indexOf(" MENU") >= 0 && sLine.indexOf("IDR_") >= 0) { //MENU...
        iBlockType = MENU_BLOCK;
      } else if (sLine.indexOf(" DIALOG") >= 0) { //DIALOG(EX)...
        iBlockType = DIALOGEX_BLOCK;
      } else if (sLine === "STRINGTABLE") { //STRINGTABLE...
        iBlockType = STRINGTABLE_BLOCK;
      } else if (sLine.indexOf(" VERSIONINFO") >= 0) { //VERSIONINFO...
        iBlockType = VERSIONINFO_BLOCK;
      } else if (sLine.indexOf(" ACCELERATORS") >= 0) { //ACCELERATORS...
        iBlockType = ACCELERATORS_BLOCK;
      } else if (sLine.indexOf(" BITMAP ") >= 0) { //BITMAP...
        iBlockType = BITMAP_BLOCK;
        sLcLine = "//" + sLcLine;
      } else if (sLine === "BEGIN") { //BEGIN...
        //IGNORE FOR SPEEDUP!
      } else if (sLine === "END") { //END...
        if (iBlockType === STRINGTABLE_BLOCK || iBlockType === TEXTINCLUDE_BLOCK) { //If inside STRINGTABLE or TEXTINCLUDE...
          iBlockType = NO_BLOCK;
        }
      } else if (sLine !== "") { //If NOT empty line...
        switch (iBlockType) {
          case NO_BLOCK:
            var oMatch0 = /LANGUAGE (LANG_\w*, SUBLANG_\w*)/.exec(sLine);
            if (oMatch0) { //LANGUAGE...
              sString = oMatch0[1];
              sComment = "LANGUAGE, SUBLANGUAGE";
            }
            break;

          case MENU_BLOCK:
          case DIALOGEX_BLOCK:
          case STRINGTABLE_BLOCK:
            if (sLine.indexOf("\"") >= 0) { //If quote found (for speedup)...
              //--------------------------------------------------------------------------------
              // Replace 1st string literal only - 2nd string literal specifies control class!
              //--------------------------------------------------------------------------------
              var oMatch2 = /"((?:""|[^"])*)"/.exec(sLine);
              if (oMatch2) { //String...
                var sTemp = oMatch2[1];
                if (sTemp !== "" && !(sTemp in oBlacklist)) { //If NOT blacklisted...
                  sLcLine = replacei(sLcLine, "\"" + sTemp + "\"", "\"" + sReference + "\"");
                  sString = sTemp.replace(/\"\"/g, "\\\"");
                  var oMatch3 = /\/\/#\. (.*?)$/.exec(sLine);
                  var oMatch4 = /\/\/msgctxt (.*?)$/.exec(sLine);
                  if (oMatch3) { //If found a comment for the translators...
                    sComment = oMatch3[1].replace(/^\s+|\s+$/g, "");
                  } else if (oMatch4) { //If found a context for the translation...
                    sContext = oMatch4[1].replace(/^\s+|\s+$/g, "");
                    sComment = sContext;
                  }
                }
              }
            }
            break;

          case VERSIONINFO_BLOCK:
            var oMatch5 = /BLOCK "([0-9A-F]+)"/.exec(sLine);
            var oMatch6 = /VALUE "Comments", "(.*?)\\?0?"/.exec(sLine);
            var oMatch7 = /VALUE "Translation", (.*?)$/.exec(sLine);
            if (oMatch5) { //StringFileInfo.Block...
              sString = oMatch5[1];
              sComment = "StringFileInfo.Block";
            } else if (oMatch6) { //StringFileInfo.Comments...
              sString = oMatch6[1];
              sComment = "You should use a string like \"Translated by \" followed by the translator names for this string. It is ONLY VISIBLE in the StringFileInfo.Comments property from the final resource file!";
            } else if (oMatch7) { //VarFileInfo.Translation...
              sString = oMatch7[1];
              sComment = "VarFileInfo.Translation";
            }
            break;
        }
      }
      
      if (sString !== "") {
        var sKey = sContext + sString;
        var oString = { "Comment": "", "References": "", "Context": "", "Id": "", "Str": "" };
        if (sKey in oStrings) { //If the key is already used...
          oString = oStrings[sKey];
        }
        if (sComment !== "") {
          oString.Comment = sComment;
        }
        if (oString.References !== "") {
          oString.References = oString.References + "\t" + sReference;
        } else {
          oString.References = sReference;
        }
        oString.Context = sContext;
        oString.Id = sString;
        oString.Str = "";
        
        if (sKey in oStrings) { //If the key is already used...
          oStrings[sKey] = oString;
        } else { //If the key is NOT already used...
          oStrings[sContext + sString] = oString;
        }
      }
      oLcFile.WriteLine(sLcLine);
      fContinuation = (sLine !== "") && ",|".indexOf(sLine.substring(sLine.length - 1)) >= 0;
    }
    oLcFile.WriteLine("en-US.pot RCDATA \"en-US.pot\"");
    oRcFile.Close();
    oLcFile.Close();
  }
  return oStrings;
}

////
// ...
function GetStringBlacklist(sTxtFilePath) {
  var oBlacklist = {};
  if (oFSO.FileExists(sTxtFilePath)) { //If the blacklist file exists...
    var oTxtFile = oFSO.OpenTextFile(sTxtFilePath, ForReading);
    while (!oTxtFile.AtEndOfStream) { //For all lines...
      var sLine = oTxtFile.ReadLine().replace(/^\s+|\s+$/g, "");
      if (sLine !== "") {
        if (!(sLine in oBlacklist)) { //If the key is NOT already used...
          oBlacklist[sLine] = true;
        }
      }
    }
    oTxtFile.Close();
  }
  return oBlacklist;
}

////
// ...
function CreateMasterPotFile(sPotPath, oStrings) {
  var oPotFile = oFSO.CreateTextFile(sPotPath, true);
  
  oPotFile.WriteLine("# This file is part of Frhed <http://frhed.sourceforge.net/>");
  oPotFile.WriteLine("# Released under the \"GNU General Public License\"");
  oPotFile.WriteLine("#");
  oPotFile.WriteLine("msgid \"\"");
  oPotFile.WriteLine("msgstr \"\"");
  oPotFile.WriteLine("\"Project-Id-Version: Frhed\\n\"");
  oPotFile.WriteLine("\"Report-Msgid-Bugs-To: http://sourceforge.net/tracker/?group_id=13216&atid=113216\\n\"");
  oPotFile.WriteLine("\"POT-Creation-Date: " + GetPotCreationDate() + "\\n\"");
  oPotFile.WriteLine("\"PO-Revision-Date: \\n\"");
  oPotFile.WriteLine("\"Last-Translator: \\n\"");
  oPotFile.WriteLine("\"Language-Team: English <frhed-devel@lists.sourceforge.net>\\n\"");
  oPotFile.WriteLine("\"MIME-Version: 1.0\\n\"");
  oPotFile.WriteLine("\"Content-Type: text/plain; charset=UTF-8\\n\"");
  oPotFile.WriteLine("\"Content-Transfer-Encoding: 8bit\\n\"");
  oPotFile.WriteLine("\"X-Poedit-Language: English\\n\"");
  oPotFile.WriteLine("\"X-Poedit-SourceCharset: UTF-8\\n\"");
  oPotFile.WriteLine("\"X-Poedit-Basepath: ../../FRHED\\n\"");
  //oPotFile.WriteLine("\"X-Generator: CreateMasterPotFile.js\\n\"");
  oPotFile.WriteLine("");
  for (var sKey in oStrings) { //For all strings...
    var oString = oStrings[sKey];
    if (oString.Comment !== "") { //If comment exists...
      oPotFile.WriteLine("#. " + oString.Comment);
    }
    var aReferences = oString.References.split("\t");
    for (var i = 0; i < aReferences.length; i++) { //For all references...
      oPotFile.WriteLine("#: " + aReferences[i]);
    }
    oPotFile.WriteLine("#, c-format");
    if (oString.Context !== "") { //If context exists...
      oPotFile.WriteLine("msgctxt \"" + oString.Context + "\"");
    }
    oPotFile.WriteLine("msgid \"" + oString.Id + "\"");
    oPotFile.WriteLine("msgstr \"\"");
    oPotFile.WriteLine("");
  }
  oPotFile.Close();
}

////
// ...
function GetPotCreationDate() {
  var oNow = new Date();
  var sYear = oNow.getFullYear();
  var sMonth = oNow.getMonth() + 1;
  if (sMonth < 10) { sMonth = "0" + sMonth; }
  var sDay = oNow.getDate();
  if (sDay < 10) { sDay = "0" + sDay; }
  var sHour = oNow.getHours();
  if (sHour < 10) { sHour = "0" + sHour; }
  var sMinute = oNow.getMinutes();
  if (sMinute < 10) { sMinute = "0" + sMinute; }
  
  return sYear + "-" + sMonth + "-" + sDay + " " + sHour + ":" + sMinute + "+0000";
}

////
// ...
function InfoBox(sText, iSecondsToWait) {
  if (!bRunFromCmd) { //If run from command line...
    var oShell = WScript.CreateObject("WScript.Shell");
    return oShell.Popup(sText, iSecondsToWait, WScript.ScriptName, 64);
  } else { //If NOT run from command line...
    WScript.Echo(sText);
  }
}

////
// ...
function GetArchiveBit(sFilePath) {
  if (oFSO.FileExists(sFilePath)) { //If the file exists...
    var oFile = oFSO.GetFile(sFilePath);
    if (oFile.Attributes & 32) { //If archive bit set...
      return true;
    }
  }
  return false;
}

////
// ...
function SetArchiveBit(sFilePath, bValue) {
  if (oFSO.FileExists(sFilePath)) { //If the file exists...
    var oFile = oFSO.GetFile(sFilePath);
    if (oFile.Attributes & 32) { //If archive bit set...
      if (!bValue) {
        oFile.Attributes -= 32;
      }
    } else { //If archive bit NOT set...
      if (bValue) {
        oFile.Attributes += 32;
      }
    }
  }
}
