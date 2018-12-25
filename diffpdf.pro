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
LIBS	     += -lpoppler-qt4
win32 {
    CONFIG += release
#   QMAKE_CC = gcc
#   QMAKE_CXX = g++
    COMPNAME = $(COMPUTERNAME)
    eval(COMPNAME = "IT585") {
        QTMINGWHOME = D:\kp\bin\Qt\5.10.0\mingw53_32
        }
    eval(COMPNAME = "BAJ4XP") {
        QTMINGWHOME = D:\kp\bin\Qt\Qt5.3.2\5.3\mingw482_32
        }
    INCLUDEPATH += $${QTMINGWHOME}\include\QtWidgets
    }
exists($(HOME)/opt/poppler020/) {
    message(Using locally built Poppler library)
    INCLUDEPATH += $(HOME)/opt/poppler020/include/poppler/cpp
    INCLUDEPATH += $(HOME)/opt/poppler020/include/poppler/qt4
    LIBS += -Wl,-rpath -Wl,$(HOME)/opt/poppler020/lib -Wl,-L$(HOME)/opt/poppler020/lib
    }
else {
    exists(/poppler_lib) {
        message(Using locally built Poppler library on Windows)
        INCLUDEPATH += /c/poppler_lib/include/poppler/cpp
        INCLUDEPATH += /c/poppler_lib/include/poppler/qt4
        LIBS += -Wl,-rpath -Wl,/c/poppler_lib/bin -Wl,-L/c/poppler_lib/bin
        }
    else {
        exists(/usr/include/poppler/qt4) {
            INCLUDEPATH += /usr/include/poppler/cpp
            INCLUDEPATH += /usr/include/poppler/qt4
            }
        else {
            exists(/usr/local/include/poppler/qt4) {
                INCLUDEPATH += /usr/local/include/poppler/cpp
                INCLUDEPATH += /usr/local/include/poppler/qt4
                }
            else {
                INCLUDEPATH += ../poppler/src_kp/poppler/cpp
                INCLUDEPATH += ../poppler/src_kp/poppler/qt4/src
                }
            }
        }
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
