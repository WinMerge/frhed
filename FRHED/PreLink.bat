cd
echo %0
echo $(IntDir) = %1
echo $(TargetPath) = %2
echo $(PlatformTarget) = %3
cd ..\Translations\Frhed
cscript CreateMasterPotFile.vbs
cscript UpdatePoFilesFromPotFile.vbs
cd ..\..\FRHED
rc "/fo%~1\lang.res" /i.. ..\Translations\Frhed\heksedit.rc
mkdir "%~2\..\Languages"
link /DLL /NOENTRY /MACHINE:%~3 "/OUT:%~2\..\Languages\heksedit.lng" "%~1\lang.res"
editbin.exe /OSVERSION:4.0 /SUBSYSTEM:WINDOWS,4.0 "%~2\..\Languages\heksedit.lng"
copy ..\Translations\Frhed\*.po "%~2\..\Languages"
