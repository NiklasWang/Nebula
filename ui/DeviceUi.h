#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

namespace nebula {

class DeviceUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    QString getName();
    QSize getSize();

public:
    DeviceUi(QMainWindow *window, QString &name, int32_t id);
    ~DeviceUi();

private:
    int32_t mId;
    QString mName;

private:
    QMainWindow *mMainWindow;
    QWidget     *mCentralWidget;
    QGroupBox   *mGroupBox;
    QWidget     *mGridLayoutWidget;
    QGridLayout *mGridLayout;
    QLabel *mPictureLabel0;
    QLabel *mTextLabel0;
    QLabel *mPictureLabel1;
    QLabel *mTextLabel1;
    QLabel *mPictureLabel2;
    QLabel *mTextLabel2;
    QLabel *mPictureLabel3;
    QLabel *mTextLabel3;
    QLabel *mResultLabel;
    QTextEdit *mDebugEditor;
};

}

#endif // DEVICEUI_H
