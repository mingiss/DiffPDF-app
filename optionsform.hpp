#ifndef OPTIONSFORM_HPP
#define OPTIONSFORM_HPP
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

#include <QBrush>
#include <QDialog>
#include <QPen>

#include "generic.hpp"

class QCheckBox;
class QComboBox;
class QDialogButtonBox;
class QDoubleSpinBox;
class QSpinBox;
class QTabWidget;


class OptionsForm : public QDialog
{
    Q_OBJECT

public:
    OptionsForm(qPen *pens, QBrush *brushes, qreal *ruleWidth,
            bool *showToolTips, bool *combineTextHighlighting,
            int *cacheSize, int *alpha, int *squareSize,
            QWidget *parent=0);

private slots:
    void updateColor(int index, DiffTypes eDiffType);
    void updateAppColor(int index);
    void updateInsColor(int index);
    void updateDelColor(int index);
    void updateRepColor(int index);

    void updateBrushStyle(int index);
    void updatePenStyle(int index);
    void updateSwatches();
    void updateUi();
    void accept();

private:
    void createWidgets();
    void createLayout();
    void createConnections();

    QTabWidget *tabWidget;
    QComboBox *colorComboBoxes[NumOfDiffTypes];
    QComboBox *inscolComboBox;
    QComboBox *delcolComboBox;
    QComboBox *repcolComboBox;
    QComboBox *brushStyleComboBox;
    QComboBox *penStyleComboBox;
    QSpinBox *alphaSpinBox;
    QSpinBox *squareSizeSpinBox;
    QDoubleSpinBox *ruleWidthSpinBox;
    QCheckBox *showToolTipsCheckBox;
    QCheckBox *combineTextHighlightingCheckBox;
    QSpinBox *cacheSizeSpinBox;
    QDialogButtonBox *buttonBox;

    qPen *m_pens;
    QBrush *m_brushes;
    qreal *m_ruleWidth;
    bool *m_showToolTips;
    bool *m_combineTextHighlighting;
    int *m_cacheSize;
    int *m_alpha;
    int *m_squareSize;
    qPen pens[NumOfDiffTypes];
    QBrush brushes[NumOfDiffTypes];
};

#endif // OPTIONSFORM_HPP


