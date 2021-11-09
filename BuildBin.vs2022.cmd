cd /d "%~dp0"

del /s Build\*.exe
del /s BuildTmp\*.res

setlocal
for /f "usebackq tokens=*" %%i in (`"%programfiles(x86)%\microsoft visual studio\installer\vswhere.exe" -version [17.0^,18.0^) -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
  set InstallDir=%%i
)
if exist "%InstallDir%\Common7\Tools\vsdevcmd.bat" (
  call "%InstallDir%\Common7\Tools\vsdevcmd.bat %*
)
MSBuild FRHED.vs2019.sln /t:rebuild /p:Configuration=Release /p:Platform="Win32" || pause
MSBuild FRHED.vs2019.sln /t:rebuild /p:Configuration=Release /p:Platform="x64" || pause
MSBuild FRHED.vs2019.sln /t:rebuild /p:Configuration=Release /p:Platform="ARM64" || pause

if exist "%SIGNBAT_PATH%" (
  "%SIGNBAT_PATH%" Build\FRHED\Win32\Release\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\Win32\Release\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\Win32\Release\Languages\heksedit.lng
  "%SIGNBAT_PATH%" Build\FRHED\x64\Release\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\x64\Release\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\x64\Release\Languages\heksedit.lng
  "%SIGNBAT_PATH%" Build\FRHED\ARM64\Release\frhed.exe
  "%SIGNBAT_PATH%" Build\FRHED\ARM64\Release\hekseditU.dll
  "%SIGNBAT_PATH%" Build\FRHED\ARM64\Release\Languages\heksedit.lng
)

endlocal

