:: wrapper script to call DiffPDF executable

:: PATH = D:\kp\bin\Qt\Qt5.3.2\5.3\mingw482_32\bin;%PATH%
:: set QT_PLUGIN_PATH=D:\bin\utils\texgr\DiffPDF\plugins 

:: original DiffPDF executable v.2.1.3
:: D:\bin\utils\diffpdf\diffpdf.exe -a %*

:: vtex modified version, fork from v.2.1.4 
D:\bin\utils\texgr\DiffPDF\diffpdf_vtex.exe -a %*

