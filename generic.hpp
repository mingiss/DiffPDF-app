#ifndef GENERIC_HPP
#define GENERIC_HPP
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

#include <QGlobalStatic>
#if QT_VERSION >= 0x050000
#include <poppler-qt5.h>
#else
#include <poppler-qt4.h>
#endif
#include <QMetaType>
#include <QPair>
#include <QPixmap>
#include <QSet>
#include <QPen>

class QColor;
class QMimeData;
class QRectF;

#if QT_VERSION >= 0x040600
typedef QSharedPointer<Poppler::Document> PdfDocument;
typedef QSharedPointer<Poppler::Page> PdfPage;
typedef QSharedPointer<Poppler::TextBox> PdfTextBox;
#else
typedef std::tr1::shared_ptr<Poppler::Document> PdfDocument;
typedef std::tr1::shared_ptr<Poppler::Page> PdfPage;
typedef std::tr1::shared_ptr<Poppler::TextBox> PdfTextBox;
#endif
typedef QList<PdfTextBox> TextBoxList;

enum InitialComparisonMode{CompareAppearance=0, CompareCharacters=1,
                           CompareWords=2};

enum Debug{DebugOff, DebugShowTexts, DebugShowTextsAndYX};

const int POINTS_PER_INCH = 72;

typedef QSet<int> Ranges;
typedef QPair<Ranges, Ranges> RangesPair;

enum DiffTypes
{
    AppDiff,        // visual appearance difference
    InsDiff,        // insertion
    DelDiff,        // deletion
    RepDiff,        // replace
    NumOfDiffTypes
};

// combining flags for SequenceMatcher::m_iDiffTypeMask
#define DIFF_TYPE_INSERT  0x01
#define DIFF_TYPE_DELETE  0x02
#define DIFF_TYPE_REPLACE 0x04
#define DIFF_TYPE_ALL     (DIFF_TYPE_INSERT | DIFF_TYPE_DELETE | DIFF_TYPE_REPLACE)

// Qt derived classes preserving symbolic color name
class qColor: public QColor
{
public:
    QString m_sColorName;

    qColor(const QString& name): QColor(name), m_sColorName(name) {}
};
class qPen: public QPen
{
public:
    QString m_sColorName;

    qPen(): QPen() {}
    qPen(const qPen& pen): QPen(pen), m_sColorName(pen.m_sColorName) {}
    qPen(const QPen& pen): QPen(pen), m_sColorName(pen.color().name()) {}
    void setColor(const char* name) { qColor color(name); setColor(color); m_sColorName = name; }
    void setColor(const QString& name) { qColor color(name); setColor(color); m_sColorName = name; }
    void setColor(const qColor& color) { QPen::setColor(color); m_sColorName = color.m_sColorName; }
};

struct PagePair
{
    PagePair(int l=-2, int r=-2, bool v=false) // -1 means empty page from now
        : left(l), right(r), hasVisualDifference(v) {}

    bool isNull() { return left == -2 || right == -2; }

    const int left;
    const int right;
    const bool hasVisualDifference;
};
Q_DECLARE_METATYPE(PagePair)


inline const QChar canonicalizedCharacter(const QChar &in)
{
    QChar out = in;
    const ushort c = in.unicode();
    switch (c) {
        case 0x93:   out = QChar(0x201C); break; // “
        case 0x94:   out = QChar(0x201D); break; // ”
        case 0xAD:   // fallthrough (soft-hyphen)
        case 0x2D:   // fallthrough (hyphen-minus)
        case 0x2010: // fallthrough (hyphen)
        case 0x2011: // fallthrough (non-breaking hyphen)
        case 0x2043: out = '-'; break; // (hyphen-bullet)
    }
    return out;
}


void scaleRect(int dpi, QRectF *rect);
int pointValueForPixelOffset(const double dpi, int px);
int pixelOffsetForPointValue(const double dpi, int pt);
QRectF rectForMargins(const int width, const int height, const int top,
        const int bottom, const int left, const int right);
Ranges unorderedRange(int end, int start=0);

QPixmap colorSwatch(const QColor &color);
QPixmap brushSwatch(const Qt::BrushStyle style, const QColor &color);
QPixmap penStyleSwatch(const Qt::PenStyle style, const QColor &color);

const TextBoxList getTextBoxes(PdfPage page, const QRectF &rect=QRect());

const QString strippedFilename(const QString &filename);
const QStringList droppedFilenames(const QMimeData *mimeData);
const QRect resizeRect(const QRect &pageRect, const QSize &pixmapSize);

/* // Not needed
const int roundedToNearest(const int x, const int multiple)
{
    Q_ASSERT(multiple)
    const int remainder = x % multiple;
    return (remainder == 0) ? x : x + multiple - remainder;
}
*/

#endif // GENERIC_HPP
