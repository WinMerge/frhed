cd /d "%~dp0"

set DISTDIR=.\Dist
set path="%ProgramFiles%\7-zip";"%ProgramFiles(x86)%\7-zip";%path%

if "%1" == "" (
  call :BuildArc x86 || goto :eof
  call :BuildArc x64 || goto :eof
  call :BuildArc ARM || goto :eof
  call :BuildArc ARM64 || goto :eof
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
copy GPL.txt "%DISTDIR%\%1\frhed\""

7z.exe a -tzip "%DISTDIR%\frhed-%EXE_VERSION%-%1.zip" "%DISTDIR%\%1\frhed\"

goto :eof

:GET_EXE_VERSION

SET EXE_PATH=%1
WMIC Path CIM_DataFile WHERE Name='%EXE_PATH:\=\\%' Get Version | findstr /v Version > _tmp_.txt
set /P EXE_VERSIONTMP=<_tmp_.txt
set EXE_VERSION=%EXE_VERSIONTMP: =%
del _tmp_.txt
goto :eof
