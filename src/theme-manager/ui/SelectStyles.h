/* 
 * File:   selectStyles.h
 * Author: sigfried
 *
 * Created on October 17, 2014, 2:42 PM
 */

#ifndef _SELECTSTYLES_H
#define	_SELECTSTYLES_H

#include "ui_selectStyles.h"

class SelectStyles : public QDialog {
    Q_OBJECT
public:
    SelectStyles();
    virtual ~SelectStyles();
    void getQssStyles(QStringList* qssStyles);
    void getIconThemes(QStringList* iconThemes);
private:
    Ui::selectStyles widget;
};

#endif	/* _SELECTSTYLES_H */
