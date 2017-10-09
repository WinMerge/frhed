cd /d "%~dp0"

del /s Build\*.exe
del /s BuildTmp\*.res

setlocal
for /f "usebackq tokens=*" %%i in (`"%programfiles(x86)%\microsoft visual studio\installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
  set InstallDir=%%i
)
if exist "%InstallDir%\Common7\Tools\vsdevcmd.bat" (
  call "%InstallDir%\Common7\Tools\vsdevcmd.bat %*
)
MSBuild FRHED.vs2017.sln /t:rebuild /p:Configuration=UnicodeRelease /p:Platform="Win32" || pause
MSBuild FRHED.vs2017.sln /t:rebuild /p:Configuration=UnicodeRelease /p:Platform="x64" || pause

if exist "%SIGNBAT_PATH%" (
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\Win32\UnicodeRelease\Languages\heksedit.lng
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\x64\UnicodeRelease\Languages\heksedit.lng
)

endlocal

