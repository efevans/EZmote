#include <Windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Clipboard.h"

#define ALT1 1
#define ALT2 2
#define ALT3 3

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->makeConnections();

    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT1, MOD_ALT | MOD_NOREPEAT, 0x31);
}

MainWindow::~MainWindow()
{
    delete ui;
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT1);
}

void MainWindow::makeConnections()
{
    connect(ui->alt1, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt2, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt3, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG *msg = reinterpret_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY)
    {
        std::string str = stringHotKeys["alt1"];
        Clipboard clipboard;
        clipboard.copy_to_clipboard(str);
        *result = 0;
        return true;
    }

    return false;
}


void MainWindow::on_keylineedit_edited(QString str)
{
    // get object name of sender as std::string
    KeyLineEdit *edit = qobject_cast<KeyLineEdit*>(sender());
    std::string senderName = edit->property("objectName").toString().toLocal8Bit().constData();

    // get lineedit string as std::string
    std::string dataStr = str.toLocal8Bit().constData();

    // input into map<std::string, std::string>
    stringHotKeys[senderName] = dataStr;
}
