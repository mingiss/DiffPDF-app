# NOTES.txt
# CHANGES
# README
# help.html
# diffpdf.1
#DEFINES	     += DEBUG
HEADERS	     += mainwindow.hpp
SOURCES      += mainwindow.cpp
HEADERS	     += textitem.hpp
SOURCES	     += textitem.cpp
HEADERS	     += aboutform.hpp
SOURCES      += aboutform.cpp
HEADERS	     += optionsform.hpp
SOURCES      += optionsform.cpp
HEADERS	     += helpform.hpp
SOURCES      += helpform.cpp
HEADERS	     += saveform.hpp
SOURCES      += saveform.cpp
HEADERS	     += generic.hpp
SOURCES	     += generic.cpp
HEADERS	     += sequence_matcher.hpp
SOURCES      += sequence_matcher.cpp
SOURCES      += main.cpp
HEADERS	     += lineedit.hpp
SOURCES	     += lineedit.cpp
HEADERS	     += label.hpp
SOURCES	     += label.cpp
RESOURCES    += resources.qrc
TRANSLATIONS += diffpdf_cz.ts
TRANSLATIONS += diffpdf_fr.ts
TRANSLATIONS += diffpdf_de.ts
CODECFORTR    = UTF-8
QMAKE_CXXFLAGS += -std=c++11
QTVERS = qt4
win32 {
    DEFINES += poppler_cpp_EXPORTS
    DEFINES += poppler_qt5_EXPORTS
    DEFINES += QT_STATIC
    CONFIG  += staticlib
    CONFIG  += release
#   QMAKE_CC = gcc
#   QMAKE_CXX = g++
#    COMPNAME = $$(COMPUTERNAME)
#    contains(COMPNAME, IT585) {
#        # QTMINGWHOME = D:/kp/bin/Qt/5.10.0/mingw53_32
#        QTMINGWHOME = D:/kp/bin/Qt/Qt5.10.0/5.10.0/mingw53_32  
#        QTVERS = qt5
#        }
#    contains(COMPNAME, BAJ4XP) {
        QTMINGWHOME = D:/kp/bin/Qt/Qt5.3.2/5.3/mingw482_32
        QTVERS = qt5
#        }
    INCLUDEPATH += $${QTMINGWHOME}/include
    INCLUDEPATH += $${QTMINGWHOME}/include/QtWidgets
    INCLUDEPATH += $${QTMINGWHOME}/include/QtPrintSupport
    } 
exists($(HOME)/opt/poppler020/) {
    message(Using locally built Poppler library)
    INCLUDEPATH += $(HOME)/opt/poppler020/include/poppler/cpp
    INCLUDEPATH += $(HOME)/opt/poppler020/include/poppler/$${QTVERS}
    LIBS += -Wl,-rpath -Wl,$(HOME)/opt/poppler020/lib -Wl,-L$(HOME)/opt/poppler020/lib
    }
else {
    exists(/c/poppler_lib) {
        message(Using locally built Poppler library on Windows)
        INCLUDEPATH += /c/poppler_lib/include/poppler/cpp
        INCLUDEPATH += /c/poppler_lib/include/poppler/$${QTVERS}
        LIBS += -Wl,-rpath -Wl,/c/poppler_lib/bin -Wl,-L/c/poppler_lib/bin
        }
    else {
        exists(/usr/include/poppler/$${QTVERS}) {
            INCLUDEPATH += /usr/include/poppler/cpp
            INCLUDEPATH += /usr/include/poppler/$${QTVERS}
            }
        else {
            exists(/usr/local/include/poppler/$${QTVERS}) {
                INCLUDEPATH += /usr/local/include/poppler/cpp
                INCLUDEPATH += /usr/local/include/poppler/$${QTVERS}
                }
            else {
                # INCLUDEPATH += ../../../poppler/src_kp/poppler/cpp
                # INCLUDEPATH += ../../../poppler/src_kp/poppler/$${QTVERS}/src
                INCLUDEPATH += libs/poppler/cpp
                INCLUDEPATH += libs/poppler/$${QTVERS}/src
                # LIBS        += -Wl,-Llibs/poppler/$${QTVERS}/release
                LIBS        += -Wl,-Lbin/win32 
                # LIBS        += -lfreetype
                # LIBS        += -Wl,-Llibs/freetype2/objs/.libs 
                # LIBS        += -Wl,-Llibs/libjpeg/.libs
                }
            }
        }
    }
LIBS	     += -lpoppler-$${QTVERS}
win32 {
    LIBS += -Wl,-L$${QTMINGWHOME}/lib \
        -lQt5Widgets \
        -lQt5Xml \
        -lQt5PrintSupport \
\
\#        -lQt5Core \
\#        -lQt5Gui \
\#        -lQt5AxContainer \
\#        -lQt5Qml \
\#        -lQt5AxBase \
\#        -lQt5UiTools \
\
\#        -lEnginio \
\#        -lQt5Bluetooth \
\#        -lQt5CLucene \
\#        -lQt5Concurrent \
\#        -lQt5Declarative \
\#        -lQt5Designer \
\#        -lQt5DesignerComponents \
\#        -lQt5Help \
\#        -lQt5Multimedia \
\#        -lQt5MultimediaQuick_p \
\#        -lQt5MultimediaWidgets \
\#        -lQt5Network \
\#        -lQt5Nfc \
\#        -lQt5OpenGL \
\#        -lQt5OpenGLExtensions \
\#        -lQt5PlatformSupport \
\#        -lQt5Positioning \
\#        -lQt5QmlDevTools \
\#        -lQt5Quick \
\#        -lQt5QuickParticles \
\#        -lQt5QuickTest \
\#        -lQt5QuickWidgets \
\#        -lQt5Script \
\#        -lQt5ScriptTools \
\#        -lQt5Sensors \
\#        -lQt5SerialPort \
\#        -lQt5Sql \
\#        -lQt5Svg \
\#        -lQt5Test \
\#        -lQt5WebKit \
\#        -lQt5WebKitWidgets \
\#        -lQt5WebSockets \
\#        -lQt5WinExtras \
\#        -lQt5XmlPatterns \
\#        -lqtmain
\
\#        -lQt5AxServer \
\#        -lQt5Bootstrap \
        -ljpeg
    }
#exists($(HOME)/opt/podofo09/) {
#    message(Using locally built PoDoFo library)
#    INCLUDEPATH += $(HOME)/opt/podofo09/include/poppler/cpp
#    INCLUDEPATH += $(HOME)/opt/podofo09/include/poppler/qt4
#    LIBS += -Wl,-rpath -Wl,$(HOME)/opt/podofo09/lib64 -Wl,-L$(HOME)/opt/podofo09/lib64
#} else {
#    exists(/usr/include/podofo) {
#	INCLUDEPATH += /usr/include/podofo
#    } else {
#	INCLUDEPATH += /usr/local/include/podofo
#    }
#}
