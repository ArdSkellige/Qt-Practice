#include "widget.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Qt::WindowFlags flags = Qt::Widget;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::WindowTitleHint;
    this->setWindowFlags(flags);
    this->setWindowTitle(tr("Signals and Slots"));
    this->setMaximumSize(800, 300);

    // создаю панель:
    frame = new QFrame(this);
    frame->setFrameStyle(QFrame::Sunken || QFrame::Box);

    // создаём элементы управления:
    QPushButton* closeBut = new QPushButton(QObject::tr("Exit"), this);
    QObject::connect(closeBut, SIGNAL(clicked(bool)), this, SLOT(close()));
    enableDisable = new QPushButton(QObject::tr("Disable"), this);
    QComboBox* frameStyles = createComboBox();

    label = createLabel();
    lineEdit = createLineEdit();
    spinBox = createSpinbox();
    slider = createSlider();

    // коннектим:
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(textChanged(QString)), lineEdit, SLOT(setText(QString)));
    QObject::connect(spinBox, SIGNAL(textChanged(QString)), label, SLOT(setText(QString)));

    QObject::connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(mySlot(QString)));
    QObject::connect(this, SIGNAL(mySignal(int)), slider, SLOT(setValue(int)));

    QObject::connect(frameStyles, SIGNAL(activated(int)), this, SLOT(slotChangeLayout(int)));
    QObject::connect(enableDisable, SIGNAL(clicked(bool)), this, SLOT(slotEnableDisable()));

    // создание главной компоновки:
    QHBoxLayout* mainLayout = new QHBoxLayout; // главная компоновка окна
    this->setLayout(mainLayout);

    // создание главной компоновки панели(for QFrame):
    QHBoxLayout *frameLayout = new QHBoxLayout(frame); // главная компоновка панели
    frameLayout->setObjectName("Frame Horizon Layout");
    frameLayout->addWidget(label);
    frameLayout->addWidget(lineEdit);
    frameLayout->addWidget(spinBox);
    frameLayout->addWidget(slider);

    // создание компоновки с кнопками:
    QVBoxLayout* buttLayout = new QVBoxLayout; // (вложенные) компоновки создаются БЕЗ родителя
    buttLayout->addWidget(frameStyles);
    buttLayout->addWidget(enableDisable);
    buttLayout->addWidget(closeBut);

    // добавление дочерних компоновок в главную:
    mainLayout->addWidget(frame);
    mainLayout->addLayout(buttLayout);

    spinBox->setValue(10);
}

Widget::~Widget()
{
}

QLabel* Widget::createLabel()
{
    QLabel* lab = new QLabel();
    lab->setFrameStyle(QFrame::Sunken || QFrame::Box);
    lab->setFixedSize(30, 20);
    lab->setAlignment(Qt::AlignCenter);
    return lab;
}

QLineEdit* Widget::createLineEdit()
{
    QLineEdit* lineEd = new QLineEdit();
    lineEd->setMaximumSize(40,20);
    QIntValidator* valid = new QIntValidator(0, 50);
    lineEd->setValidator(valid);
    return lineEd;
}

QSpinBox* Widget::createSpinbox()
{
    QSpinBox* spinB = new QSpinBox();
    //spinB->setMaximumSize(100, 20);
    spinB->setMaximum(50);
    spinB->setFixedSize(100, 20);
    //spinB->setFont(QFont("Arial", 10));
    return spinB;
}

QSlider* Widget::createSlider()
{
    QSlider* slid = new QSlider();
    slid->setOrientation(Qt::Horizontal);
    slid->setMaximum(50);
    slid->setMinimumSize(150, 20);
    slid->setTickPosition(QSlider::TicksBelow);
    return slid;
}

QComboBox* Widget::createComboBox()
{
    QComboBox* frameStyle = new QComboBox();
    frameStyle->addItem("Horizontal Layout");
    frameStyle->addItem("Vertical Layout");
    frameStyle->addItem("Grid Layout");
    return frameStyle;
}

QLayout* Widget::createHBoxLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setObjectName("Frame Horizon Layout");
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(spinBox);
    layout->addWidget(slider);
}

QLayout* Widget::createVBoxLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setObjectName("Frame Vert Layout");
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(spinBox);
    layout->addWidget(slider);
}

QLayout* Widget::createGridLayout()
{
    QGridLayout *layout = new QGridLayout(frame);
    layout->setObjectName("Frame Grid Layout");
    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 1, 0);
    layout->addWidget(spinBox, 0, 1);
    layout->addWidget(slider, 1, 1);
    layout->setAlignment(Qt::AlignHCenter);
}

void Widget::mySlot(QString str)
{
    QVariant variant(str);
    int num = variant.toInt();
    //if(num >= 0 && num <= 50)
    {
        emit this->mySignal(num);
    }
}

void Widget::slotChangeLayout(int index)
{
    delete frame->layout();
    switch(index)
    {
    case 0:
        createHBoxLayout();
        break;
    case 1:
        createVBoxLayout();
        break;
    case 2:
        createGridLayout();
        break;
    }
}

void Widget::slotEnableDisable()
{
    if(frame->isEnabled())
    {
        frame->setEnabled(false);
        enableDisable->setText("Enable");
    }
    else
    {
        frame->setEnabled(true);
        enableDisable->setText("Disable");
    }
}
