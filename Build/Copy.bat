@echo off

REM ホームディレクトリを指定する
set HOME_DIR_PATH=%~dp0..\

REM C++
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Cpp\IpatHelper-Cpp\x64"
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.lib" "%HOME_DIR_PATH%SampleApl\Cpp\IpatHelper-Cpp\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Cpp\IpatHelper-Cpp\x86"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.lib" "%HOME_DIR_PATH%SampleApl\Cpp\IpatHelper-Cpp\x86"

REM C#
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\CSharp\IpatHelper-CSharp\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\CSharp\IpatHelper-CSharp\x86"

REM Java
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Java\library\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Java\library\x86"

REM Python
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Python\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Python\x86"

REM Julia
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Julia\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%SampleApl\Julia\x86"

REM TestApp
copy "%HOME_DIR_PATH%Build\x64\IpatHelper.dll" "%HOME_DIR_PATH%TestApp\x64"
copy "%HOME_DIR_PATH%Build\x86\IpatHelper.dll" "%HOME_DIR_PATH%TestApp\x86"


