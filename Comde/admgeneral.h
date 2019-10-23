#ifndef ADMGENERAL_H
#define ADMGENERAL_H

#include <QDialog>

namespace Ui {
class admGeneral;
}

class admGeneral : public QDialog
{
    Q_OBJECT

public:
    explicit admGeneral(QString,QWidget *parent = nullptr);
    ~admGeneral();

private:
    Ui::admGeneral *ui;
};

#endif // ADMGENERAL_H
