/*
 * File:   selectStyles.cpp
 * Author: sigfried
 *
 * Created on October 17, 2014, 2:42 PM
 */

#include "SelectStyles.h"
#include "../c++/ThemeManager.h";

SelectStyles::SelectStyles() {
    widget.setupUi(this);
    
    getIconThemes();
    getQssStyles();
}

SelectStyles::~SelectStyles() {
}


SelectStyles::getIconThemes(QStringList* iconThemes) {
    widget.iconsComboBox->insertItems(1, iconThemes);
}


SelectStyles::getQssStyles(QStringList* qssStyles) {
    widget.qssComboBox->insertItems(1, qssStyles);
}