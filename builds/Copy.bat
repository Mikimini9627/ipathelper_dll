@echo off

REM �z�[���f�B���N�g�����w�肷��
set HOME_DIR_PATH=%~dp0..\

REM C++
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\cpp\IpatHelper-Cpp\x64"
copy "%HOME_DIR_PATH%build\x64\IpatHelper.lib" "%HOME_DIR_PATH%sample_app\cpp\IpatHelper-Cpp\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\cpp\IpatHelper-Cpp\x86"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.lib" "%HOME_DIR_PATH%sample_app\cpp\IpatHelper-Cpp\x86"

REM C#
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\csharp\IpatHelper-CSharp\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\csharp\IpatHelper-CSharp\x86"

REM Java
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\java\library\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\java\library\x86"

REM Python
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\python\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\python\x86"

REM Julia
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\julia\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%sample_app\julia\x86"

REM TestApp
copy "%HOME_DIR_PATH%build\x64\IpatHelper.dll" "%HOME_DIR_PATH%dll_test_app\x64"
copy "%HOME_DIR_PATH%build\x86\IpatHelper.dll" "%HOME_DIR_PATH%dll_test_app\x86"


