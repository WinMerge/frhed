////
// This script updates the language PO files from the master POT file.
//
// Copyright (C) 2007-2008 by Tim Gerundt
// Released under the "GNU General Public License"

var ForReading = 1;

var oFSO = new ActiveXObject("Scripting.FileSystemObject");

var bRunFromCmd = false;
if (oFSO.GetFileName(WScript.FullName).toLowerCase() === "cscript.exe") {
  bRunFromCmd = true;
}

Main();

////
// ...
function Main() {
  var oLanguage 
  
  var StartTime = new Date().getTime();
  
  InfoBox("Updating PO files from POT file...", 3);
  
  var sDir = oFSO.GetParentFolderName(WScript.ScriptFullName);
  var oEnglishPotContent = GetContentFromPoFile(sDir + "\\en-US.pot");
  if (isEmpty(oEnglishPotContent)) { throw new Error(0x80040000, "Sub Main: Error reading content from en-US.pot"); }
  var bPotChanged = GetArchiveBit("en-US.pot");
  var oLanguages = WScript.Arguments;
  if (oLanguages.Count() === 0) { var oLanguages = oFSO.GetFolder(".").Files; }
  for (var it = new Enumerator(oLanguages); !it.atEnd(); it.moveNext()) { //For all languages...
    var oLanguage = it.item();
    var sLanguage = String(oLanguage);
    if (oFSO.GetExtensionName(sLanguage).toLowerCase() === "po") {
      if (bPotChanged || GetArchiveBit(sLanguage)) { //If update necessary...
        if (bRunFromCmd) { //If run from command line...
          WScript.Echo(oFSO.GetFileName(sLanguage));
        }
        var oLanguagePoContent = GetContentFromPoFile(sLanguage);
        if (!isEmpty(oLanguagePoContent)) { //If content exists...
          CreateUpdatedPoFile(sLanguage, oEnglishPotContent, oLanguagePoContent);
        }
        SetArchiveBit(sLanguage, false);
      }
    }
  }
  
  var EndTime = new Date().getTime();
  var Seconds = (EndTime - StartTime) / 1000.0;
  
  InfoBox("All PO files updated, after " + Seconds + " second(s).", 10);
}

////
// ...
function GetContentFromPoFile(sPoPath) {
  var oMatch, sMsgId;
  var reMsgCtxt = /msgctxt "(.*)"$/i;
  var reMsgId = /^msgid "(.*)"$/i;
  var reMsgContinued = /^"(.*)"$/i;
  var oContent = {};
  var iMsgStarted = 0;
  var sMsgCtxt = "";
  var oSubContent = { "sMsgCtxt2": "", "sMsgId2": "", "sMsgStr2": "", "sTranslatorComments": "", "sExtractedComments": "", "sReferences": "", "sFlags": "" };
  var oTextFile = new ActiveXObject("ADODB.Stream");
  oTextFile.Type = 2; // adTypeText
  oTextFile.LineSeparator = 10; // adLF
  oTextFile.Charset = "UTF-8";
  oTextFile.Open();
  oTextFile.LoadFromFile(sPoPath);
  while (!oTextFile.EOS) { //For all lines...
    var sLine = oTextFile.ReadText(-2); // -2 = adReadLine
    if (sLine.length > 0) {
      if (sLine.substring(sLine.length - 1, sLine.length) === "\r") {
        sLine = sLine.substring(0, sLine.length - 1);
      }
    }
    sLine = sLine.replace(/^\s+|\s+$/g, "");
    if (sLine !== "") { //If NOT empty line...
      if (sLine.substring(0, 1) !== "#") { //If NOT comment line...
        if (reMsgCtxt.test(sLine)) { //If "msgctxt"...
          iMsgStarted = 1;
          oMatch = reMsgCtxt.exec(sLine);
          sMsgCtxt = oMatch[1];
          oSubContent.sMsgCtxt2 = sLine + "\n";
        } else if (reMsgId.test(sLine)) { //If "msgid"...
          iMsgStarted = 2;
          oMatch = reMsgId.exec(sLine);
          sMsgId = oMatch[1];
          oSubContent.sMsgId2 = sLine + "\n";
        } else if (sLine.substring(0, 8) === "msgstr \"") { //If "msgstr"...
          iMsgStarted = 3;
          oSubContent.sMsgStr2 = sLine + "\n";
        } else if (reMsgContinued.test(sLine)) { //If "msgctxt", "msgid" or "msgstr" continued...
          if (iMsgStarted === 1) {
            sMsgCtxt += oMatch[1];
            oSubContent.sMsgCtxt2 += sLine + "\n";
          } else if (iMsgStarted === 2) {
            oMatch = reMsgContinued.exec(sLine);
            sMsgId += oMatch[1];
            oSubContent.sMsgId2 += sLine + "\n";
          } else if (iMsgStarted === 3) {
            oSubContent.sMsgStr2 += sLine + "\n"
          }
        }
      } else { //If comment line...
        iMsgStarted = -1;
        switch (sLine.substring(0, 2)) {
          case "#~": //Obsolete message...
            iMsgStarted = 0;
            break;
          case "#.": //Extracted comment...
            oSubContent.sExtractedComments += sLine + "\n";
            break;
          case "#:": //Reference...
            oSubContent.sReferences += sLine + "\n";
            break;
          case "#,": //Flag...
            oSubContent.sFlags += sLine + "\n";
            break;
          default: //Translator comment...
            oSubContent.sTranslatorComments += sLine + "\n";
            break;
        }
      }
    } else if (iMsgStarted !== 0) { //If empty line AND there is pending translation...
      iMsgStarted = 0 //Don//t process same translation twice
      if (sMsgId === "") { sMsgId = "__head__"; }
      if (!((sMsgCtxt + sMsgId) in oContent)) { //If the key is NOT already used...
        oContent[sMsgCtxt + sMsgId] = oSubContent;
      }
      sMsgCtxt = "";
      var oSubContent = { "sMsgCtxt2": "", "sMsgId2": "", "sMsgStr2": "", "sTranslatorComments": "", "sExtractedComments": "", "sReferences": "", "sFlags": "" };
    }
  }
  if (iMsgStarted !== 0) { //If there is pending translation...
    if (!((sMsgCtxt + sMsgId) in oContent)) { //If the key is NOT already used...
      oContent[sMsgCtxt + sMsgId] = oSubContent;
    }
  }
  oTextFile.Close();
  return oContent;
}

////
// ...
function CreateUpdatedPoFile(sPoPath, oEnglishPotContent, oLanguagePoContent) {
  //--------------------------------------------------------------------------------
  // Backup the old PO file...
  //--------------------------------------------------------------------------------
  var sBakPath = sPoPath + ".bak";
  if (oFSO.FileExists(sBakPath)) {
    oFSO.DeleteFile(sBakPath);
  }
  oFSO.MoveFile(sPoPath, sBakPath);
  //--------------------------------------------------------------------------------
  
  var oPoFile = new ActiveXObject("ADODB.Stream");
  oPoFile.Type = 2; // adTypeText
  oPoFile.LineSeparator = 10; // adLF
  oPoFile.Charset = "UTF-8";
  oPoFile.Open();
  
  var oLanguage = oLanguagePoContent["__head__"];
  oPoFile.WriteText(oLanguage.sTranslatorComments);
  oPoFile.WriteText(oLanguage.sMsgId2);
  oPoFile.WriteText(oLanguage.sMsgStr2);
  oPoFile.WriteText("\n");
  for (var sKey in oEnglishPotContent) { //For all English content...
    if (sKey !== "__head__") {
      var oLanguage;
      var oEnglish = oEnglishPotContent[sKey];
      if (sKey in oLanguagePoContent) { //If translation exists...
        oLanguage = oLanguagePoContent[sKey];
      } else { //If translation NOT exists...
        oLanguage = oEnglish;
      }
      oPoFile.WriteText(oLanguage.sTranslatorComments);
      oPoFile.WriteText(oEnglish.sExtractedComments);
      oPoFile.WriteText(oEnglish.sReferences);
      oPoFile.WriteText(oLanguage.sFlags);
      oPoFile.WriteText(oLanguage.sMsgCtxt2);
      oPoFile.WriteText(oLanguage.sMsgId2);
      oPoFile.WriteText(oLanguage.sMsgStr2);
      oPoFile.WriteText("\n");
    }
  }
  oPoFile.SaveToFile(sPoPath, 2);
  oPoFile.Close();
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
function isEmpty(object) {
  for (var i in object) {
    return false;
  }
  return true;
}

