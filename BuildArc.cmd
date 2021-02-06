cd /d "%~dp0"

set DISTDIR=.\Dist
set path="%ProgramFiles%\7-zip";"%ProgramFiles(x86)%\7-zip";%path%

echo set args = WScript.Arguments: Set fso = CreateObject^("Scripting.FileSystemObject"^): WScript.Echo fso.GetFileVersion^(args^(0^)^): Wscript.Quit > get_file_version.vbs
for /F %%f in ('cscript //nologo get_file_version.vbs Build\FRHED\Win32\Release\frhed.exe') do SET VERSION=%%f
echo %VERSION%
del get_file_version.vbs

mkdir "%DISTDIR%\Win32\frhed\Docs" 2> NUL
mkdir "%DISTDIR%\Win32\frhed\Languages" 2> NUL
mkdir "%DISTDIR%\x64\frhed\Docs" 2> NUL
mkdir "%DISTDIR%\x64\frhed\Languages" 2> NUL

copy Build\FRHED\Win32\Release\frhed.exe "%DISTDIR%\Win32\frhed\"
copy Build\FRHED\Win32\Release\hekseditU.dll "%DISTDIR%\Win32\frhed\"
copy Build\FRHED\Win32\Release\Docs\*.* "%DISTDIR%\Win32\frhed\Docs\"
copy Build\FRHED\Win32\Release\Languages\*.* "%DISTDIR%\Win32\frhed\Languages\"
copy GPL.txt "%DISTDIR%\Win32\frhed\"
copy Build\FRHED\x64\Release\frhed.exe "%DISTDIR%\x64\frhed\"
copy Build\FRHED\x64\Release\hekseditU.dll "%DISTDIR%\x64\frhed\"
copy Build\FRHED\x64\Release\Docs\*.* "%DISTDIR%\x64\frhed\Docs\"
copy Build\FRHED\x64\Release\Languages\*.* "%DISTDIR%\x64\frhed\Languages\"
copy GPL.txt "%DISTDIR%\x64\frhed\"

7z.exe a -tzip "%DISTDIR%\frhed-%VERSION%-win32.zip" "%DISTDIR%\Win32\frhed\"
7z.exe a -tzip "%DISTDIR%\frhed-%VERSION%-x64.zip" "%DISTDIR%\x64\frhed\"

