/*
    Copyright (c) 2008-12 Qtrac Ltd. All rights reserved.
    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 2 of
    the License, or (at your option) any later version. This program is
    distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
    for more details.
*/

#include "mainwindow.hpp"
#include <QApplication>
#include <QIcon>
#include <QLibraryInfo>
#include <QLocale>
#include <QSettings>
#include <QTextCodec>
#include <QTextStream>
#include <QTranslator>
#include <QComboBox>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifdef Q_WS_MAC
    app.setCursorFlashTime(0);
#endif
    app.setOrganizationName("Qtrac Ltd.");
    app.setOrganizationDomain("qtrac.eu");
    app.setApplicationName("DiffPDF");
    app.setWindowIcon(QIcon(":/icon.png"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QTextStream out(stdout);
    QStringList args = app.arguments().mid(1);
    QSettings settings;
    InitialComparisonMode comparisonMode = static_cast<
            InitialComparisonMode>(settings.value("InitialComparisonMode",
                        CompareWords).toInt());
    const QString LanguageOption = "--language=";
    const QString sbasecolor_option = "--basecolor=";
    const QString sinscolor_option = "--inscolor=";
    const QString sdelcolor_option = "--delcolor=";
    const QString srepcolor_option = "--repcolor=";
    QString filename1;
    QString filename2;
    QString savefname;
    QString language = QLocale::system().name();
    QString sbasecolor;
    QString sinscolor;
    QString sdelcolor;
    QString srepcolor;
    bool optionsOK = true;
    Debug debug = DebugOff;
    foreach (const QString arg, args) {
        if (optionsOK && (arg == "--appearance" || arg == "-a"))
            comparisonMode = CompareAppearance;
        else if (optionsOK && (arg == "--characters" || arg == "-c"))
            comparisonMode = CompareCharacters;
        else if (optionsOK && (arg == "--words" || arg == "-w"))
            comparisonMode = CompareWords;
        else if (optionsOK && arg.startsWith(LanguageOption))
            language = arg.mid(LanguageOption.length());
        else if (optionsOK && arg.startsWith(sbasecolor_option))
            sbasecolor = arg.mid(sbasecolor_option.length());
        else if (optionsOK && arg.startsWith(sinscolor_option))
            sinscolor = arg.mid(sinscolor_option.length());
        else if (optionsOK && arg.startsWith(sdelcolor_option))
            sdelcolor = arg.mid(sdelcolor_option.length());
        else if (optionsOK && arg.startsWith(srepcolor_option))
            srepcolor = arg.mid(srepcolor_option.length());
        else if (optionsOK && (arg == "--help" || arg == "-h")) {
            out << "usage: diffpdf [options] [file1.pdf [file2.pdf]]\n\n"
                "A GUI program that compares two PDF files and shows "
                "their differences.\n"
                "\nThe files are optional and are normally set "
                "through the user interface.\n\n"
                "options:\n"
                "--help        -h   show this usage text and terminate "
                "(run the program without this option and press F1 for "
                "online help)\n"
                "--appearance  -a   set the initial comparison mode to "
                "Appearance\n"
                "--characters  -c   set the initial comparison mode to "
                "Characters\n"
                "--words       -w   set the initial comparison mode to "
                "Words\n"
                "--language=xx      set the program to use the given "
                "translation language, e.g., en for English, cz for "
                "Czech; English will be used if there is no translation "
                "available\n"
                "--basecolor=ccc    set color for appearance differences, "
                "ccc -- one of symbolic SVG color keyword names\n"
                "--inscolor=ccc     color for insertions\n"
                "--delcolor=ccc     color for deletions\n"
                "--repcolor=ccc     color for replaces\n"
                "--debug=2          write the text fed to the sequence "
                "matcher into temporary files (e.g., /tmp/page1.txt "
                "etc.)\n"
                "--debug=3          as --debug=3 but also includes "
                "coordinates in y, x order\n"
                "\nRun the program without the --help option and click "
                "About to see copyright and license details\n"
                ;
            return 0;
        }
        else if (optionsOK && (arg == "--debug" || arg == "--debug=1" ||
                               arg == "--debug1"))
            ; // basic debug mode currently does nothing (did show zones)
        else if (optionsOK && (arg == "--debug=2" || arg == "--debug2"))
            debug = DebugShowTexts;
        else if (optionsOK && (arg == "--debug=3" || arg == "--debug3"))
            debug = DebugShowTextsAndYX;
        else if (optionsOK && arg == "--")
            optionsOK = false;
        else if (filename1.isEmpty() && arg.toLower().endsWith(".pdf"))
            filename1 = arg;
        else if (filename2.isEmpty() && arg.toLower().endsWith(".pdf"))
            filename2 = arg;
        else if (savefname.isEmpty() && (!filename1.isEmpty()) && (!filename2.isEmpty()))
            savefname = arg;
        else
            out << "unrecognized argument '" << arg << "'\n";
    }

    if (!sbasecolor.isEmpty())
        settings.setValue(MainWindow::m_apszColorSettings[AppDiff], sbasecolor);
    if (!sinscolor.isEmpty())
        settings.setValue(MainWindow::m_apszColorSettings[InsDiff], sinscolor);
    if (!sdelcolor.isEmpty())
        settings.setValue(MainWindow::m_apszColorSettings[DelDiff], sdelcolor);
    if (!srepcolor.isEmpty())
        settings.setValue(MainWindow::m_apszColorSettings[RepDiff], srepcolor);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + language,
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    QTranslator appTranslator;
    appTranslator.load("diffpdf_" + language, ":/");
    app.installTranslator(&appTranslator);

    MainWindow window(debug, comparisonMode,
            savefname.isEmpty()? filename1 : QString(),
            savefname.isEmpty()? filename2 : QString(),
            language.left(2)); // We want de not de_DE etc.

    if (!savefname.isEmpty())
    {
        window.initialize_batch(filename1, filename2);
        window.save(savefname);
        return 0;
    }
    else
    {
        window.show();
        return app.exec();
    }
}

