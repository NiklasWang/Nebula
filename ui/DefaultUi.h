#ifndef UIDEFAULT_H
#define UIDEFAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>

namespace nebula {

class DefaultUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    QSize getSize();

public:
    explicit DefaultUi(QMainWindow *window);
    ~DefaultUi();

private:
    QMainWindow *mMainWindow;
    QWidget *mCentralWidget;
    QLabel  *mDefaultLabel;
    QLabel  *mDataPathLabel;
    QLineEdit   *mDataPathEdit;
    QPushButton *mSelectButton;
};

}

#endif // UIDEFAULT_H
