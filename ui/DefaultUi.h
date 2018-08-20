#ifndef UIDEFAULT_H
#define UIDEFAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>

namespace nebula {

class DefaultUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    QSize getSize();

public:
    explicit DefaultUi(QWidget *parent);
    ~DefaultUi();

private:
    QWidget     *mParent;
    QWidget     *mGridLayoutWidget;
    QGridLayout *mGridLayout;
    QLabel      *mNotifyLabel;
    QSpacerItem *mVerticalSpacer;
    QLabel      *mPathLabel;
    QLineEdit   *mPathEditor;
    QPushButton *mSelectBtn;
};

}

#endif // UIDEFAULT_H
