#define Name        "QOSGViewer"
#define Version       "0.1.0"
#define arch          "x86_64"
#define Publisher     "maisvendoo"
#define ExeName1       "qosgviewer.exe"
#define BinDir        "..\..\bin"
#define SrcDir        "..\"
#define ResourceDir   "..\resources\"
#define OsgBin        GetEnv('OSG_BIN_PATH')
#define OsgPlugins    GetEnv('OSG_PLUGINS_PATH')

[Setup]
AppId={{1982FBEB-A487-44FC-B3C7-23E48DA9871F}}

AppName={#Name}
AppVersion={#Version}
AppPublisher={#Publisher}

DefaultDirName={pf}\{#Name}
DefaultGroupName={#Name}

OutputDir=..\..\bin-setup
OutputBaseFilename={#Name}-{#arch}-v{#Version}-setup

SetupIconFile={#ResourceDir}\logo.ico

Compression=lzma
SolidCompression=yes

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]

Source: "{#BinDir}\{#ExeName1}"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#ResourceDir}\logo.ico"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "{#BinDir}\*.*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs 

[Icons]
Name: "{group}\{#Name}"; Filename: "{app}\{#ExeName1}"; IconFilename: "{app}\logo.ico"                            
Name: "{commondesktop}\{#Name}"; Filename: "{app}\{#ExeName1}"; IconFilename: "{app}\logo.ico"; Tasks: desktopicon