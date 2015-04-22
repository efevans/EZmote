#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QLineEdit>

class KeyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit KeyLineEdit(QWidget *parent);
    ~KeyLineEdit();

private:
    typedef QLineEdit super;
};

#endif // KEYLINEEDIT_H
