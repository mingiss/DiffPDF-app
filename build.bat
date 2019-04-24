:: set PATH=D:\kp\bin\Qt\Tools\mingw530_32\bin;%PATH%
:: set PATH=%PATH%;D:\kp\bin\Qt\5.10.0\mingw53_32\bin

:: set PATH=D:\kp\bin\Qt\Qt5.10.0\Tools\mingw530_32\bin;%PATH%
:: set PATH=%PATH%;D:\kp\bin\Qt\Qt5.10.0\5.10.0\mingw53_32\bin

:: set PATH=D:\kp\bin\Qt\Qt5.3.2\Tools\mingw482_32\bin;%PATH%  
:: set PATH=%PATH%;D:\kp\bin\Qt\Qt5.3.2\5.3\mingw482_32\bin

set PATH=D:\kp\bin\Qt\Qt5.3.2\5.3\mingw482_32\bin;D:\kp\bin\Qt\Qt5.3.2\Tools\mingw482_32\bin;%PATH%  


lrelease diffpdf.pro
qmake diffpdf.pro 
make


