mkdir ..\..\bin-win
copy ..\..\bin\qosgviewer.exe ..\..\bin-win\qosgviewer.exe
copy ..\..\lib\QOSGViewerWidget.dll ..\..\bin-win\QOSGViewerWidget.dll
cd ..\..\bin-win

echo "Check Qt dependences..."

windeployqt.exe qosgviewer.exe
windeployqt.exe QOSGViewerWidget.dll

echo "Copy OSG libraries..."

copy %OSG_BIN_PATH%\libosg.dll .\
copy %OSG_BIN_PATH%\libosgAnimation.dll .\
copy %OSG_BIN_PATH%\libosgDB.dll .\
copy %OSG_BIN_PATH%\libosgGA.dll .\
copy %OSG_BIN_PATH%\libosgViewer.dll .\
copy %OSG_BIN_PATH%\libOpenThreads.dll .\
copy %OSG_BIN_PATH%\libosgUtil.dll .\
copy %OSG_BIN_PATH%\libosgText.dll .\
copy %OSG_BIN_PATH%\libosgQt5.dll .\

echo "Copy OSG plugins..."

mkdir osgPlugins-3.7.0\
xcopy %OSG_BIN_PATH%\osgPlugins-3.7.0 osgPlugins-3.7.0\
cd osgPlugins-3.7.0\
del /S /Q *d.dll
cd ..\..\QOSGViewer\scripts\