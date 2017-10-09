cd /d "%~dp0"

del /s Build\*.exe
del /s BuildTmp\*.res

setlocal
call "%VS140COMNTOOLS%vsvars32.bat"
MSBuild FRHED.vs2015.sln /t:rebuild /p:Configuration=UnicodeRelease /p:Platform="Win32" || pause
MSBuild FRHED.vs2015.sln /t:rebuild /p:Configuration=UnicodeRelease /p:Platform="x64" || pause

if exist "%SIGNBAT_PATH%" (
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\Languages\heksedit.lng
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\Languages\heksedit.lng
)

endlocal

