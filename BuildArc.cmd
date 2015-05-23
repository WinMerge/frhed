cd /d "%~dp0"

set DISTDIR=.\Dist
set path="%ProgramFiles%\7-zip";"%ProgramFiles(x86)%\7-zip";%path%

echo set args = WScript.Arguments: Set fso = CreateObject^("Scripting.FileSystemObject"^): WScript.Echo fso.GetFileVersion^(args^(0^)^): Wscript.Quit > get_file_version.vbs
for /F %%f in ('cscript //nologo get_file_version.vbs Build\FRHED_vc10\Win32\UnicodeRelease\frhed.exe') do SET VERSION=%%f
echo %VERSION%
del get_file_version.vbs

mkdir "%DISTDIR%\Win32\frhed\Docs" 2> NUL
mkdir "%DISTDIR%\Win32\frhed\Languages" 2> NUL
mkdir "%DISTDIR%\x64\frhed\Docs" 2> NUL
mkdir "%DISTDIR%\x64\frhed\Languages" 2> NUL

copy Build\FRHED_vc10\Win32\UnicodeRelease\frhed.exe "%DISTDIR%\Win32\frhed\"
copy Build\FRHED_vc10\Win32\UnicodeRelease\hekseditU.dll "%DISTDIR%\Win32\frhed\"
copy Build\FRHED_vc10\Win32\UnicodeRelease\Docs\*.* "%DISTDIR%\Win32\frhed\Docs\"
copy Build\FRHED_vc10\Win32\UnicodeRelease\Languages\*.* "%DISTDIR%\Win32\frhed\Languages\"
copy GPL.txt "%DISTDIR%\Win32\frhed\"
copy Build\FRHED_vc10\x64\UnicodeRelease\frhed.exe "%DISTDIR%\x64\frhed\"
copy Build\FRHED_vc10\x64\UnicodeRelease\hekseditU.dll "%DISTDIR%\x64\frhed\"
copy Build\FRHED_vc10\x64\UnicodeRelease\Docs\*.* "%DISTDIR%\x64\frhed\Docs\"
copy Build\FRHED_vc10\x64\UnicodeRelease\Languages\*.* "%DISTDIR%\x64\frhed\Languages\"
copy GPL.txt "%DISTDIR%\x64\frhed\"

7z.exe a -tzip "%DISTDIR%\frhed-%VERSION%-win32.zip" "%DISTDIR%\Win32\frhed\"
7z.exe a -tzip "%DISTDIR%\frhed-%VERSION%-x64.zip" "%DISTDIR%\x64\frhed\"

