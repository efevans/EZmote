#include <Windows.h>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Clipboard.h"

#define ALT1 1
#define ALT2 2
#define ALT3 3
#define ALT4 4
#define ALT5 5
#define ALT6 6
#define ALT7 7
#define ALT8 8
#define ALT9 9
#define ALT0 10

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->makeConnections();
    this->registerHotKeys();
}

MainWindow::~MainWindow()
{
    delete ui;
    this->unregisterHotKeys();
}

// set up Qt connections
void MainWindow::makeConnections()
{
    connect(ui->alt1, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt2, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt3, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt4, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt5, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt6, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt7, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt8, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt9, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));

    connect(ui->alt0, SIGNAL(textEdited(QString)),
            this, SLOT(on_keylineedit_edited(QString)));
}

// register the global hotkeys
void MainWindow::registerHotKeys()
{
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT1, MOD_ALT | MOD_NOREPEAT, 0x31);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT2, MOD_ALT | MOD_NOREPEAT, 0x32);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT3, MOD_ALT | MOD_NOREPEAT, 0x33);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT4, MOD_ALT | MOD_NOREPEAT, 0x34);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT5, MOD_ALT | MOD_NOREPEAT, 0x35);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT6, MOD_ALT | MOD_NOREPEAT, 0x36);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT7, MOD_ALT | MOD_NOREPEAT, 0x37);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT8, MOD_ALT | MOD_NOREPEAT, 0x38);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT9, MOD_ALT | MOD_NOREPEAT, 0x39);
    RegisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT0, MOD_ALT | MOD_NOREPEAT, 0x30);
}

// unregister global hotkeys
void MainWindow::unregisterHotKeys()
{
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT1);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT2);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT3);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT4);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT5);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT6);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT7);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT8);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT9);
    UnregisterHotKey(reinterpret_cast<HWND>(this->winId()), ALT0);
}

// overriden function to receive and respond to messages about a register global hotkey being used
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG *msg = reinterpret_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY)
    {
        // construct the stringHotKeys map by taking the wParam value of the message, which will be
        // the key pressed not including modifiers (alt, ctrl, etc.), then prepend "alt" before it.
        std::string index = std::to_string(msg->wParam);
        index.insert(0, "alt");
        std::string str = stringHotKeys[index];

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
