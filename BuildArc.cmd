cd /d "%~dp0"

set DISTDIR=.\Dist
set path="%ProgramFiles%\7-zip";"%ProgramFiles(x86)%\7-zip";%path%

echo set args = WScript.Arguments: Set fso = CreateObject^("Scripting.FileSystemObject"^): WScript.Echo fso.GetFileVersion^(args^(0^)^): Wscript.Quit > get_file_version.vbs
for /F %%f in ('cscript //nologo get_file_version.vbs Build\FRHED\Win32\Release\frhed.exe') do SET VERSION=%%f
echo %VERSION%
del get_file_version.vbs

if "%1" == "" (
  call :BuildArc Win32 || goto :eof
  call :BuildArc ARM64 || goto :eof
  call :BuildArc x64 || goto :eof
) else (
  call :BuildArc %1 || goto :eof
)

goto :eof

:BuildArc

mkdir "%DISTDIR%\%1\frhed\Docs" 2> NUL
mkdir "%DISTDIR%\%1\frhed\Languages" 2> NUL

copy Build\FRHED\%1\Release\frhed.exe "%DISTDIR%\%1\frhed\"
copy Build\FRHED\%1\Release\hekseditU.dll "%DISTDIR%\%1\frhed\"
copy Build\FRHED\%1\Release\Docs\*.* "%DISTDIR%\%1\frhed\Docs\"
copy Build\FRHED\%1\Release\Languages\*.* "%DISTDIR%\%1\frhed\Languages\"
copy GPL.txt "%DISTDIR%\%1\frhed\"
copy GPL.txt "%DISTDIR%\ARM64\frhed\"

7z.exe a -tzip "%DISTDIR%\frhed-%VERSION%-%1.zip" "%DISTDIR%\%1\frhed\"

goto :eof
