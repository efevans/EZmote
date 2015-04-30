#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stringmanager.h"

namespace Ui {
class MainWindow;
}

class KeyLineEdit;
class StringManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    // overriden to handle windows global hotkey messages
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::MainWindow *ui;
    StringManager stringManager;

    // setup the default connections of the application
    void makeConnections();
    // register the global hotkeys
    void registerHotKeys();
    // unregister global hotkeys
    void unregisterHotKeys();

private slots:
    // updates the stringHotKeys element of signal sender's name with str
    void on_keylineedit_edited(QString str);
};

#endif // MAINWINDOW_H
