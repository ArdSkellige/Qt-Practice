#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT
    QFrame* frame;
    QLabel* label;
    QLineEdit* lineEdit;
    QSpinBox* spinBox;
    QSlider* slider;
    QPushButton* enableDisable;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QLabel* createLabel();
    QLineEdit* createLineEdit();
    QSpinBox* createSpinbox();
    QSlider* createSlider();
    QComboBox* createComboBox();

    QLayout* createHBoxLayout();
    QLayout* createVBoxLayout();
    QLayout* createGridLayout();

signals:
    void mySignal(int);
public slots:
    void mySlot(QString);
    void slotChangeLayout(int index); // для переключения компоновок
    void slotEnableDisable(); // для переключения активности фрейма
};
#endif // WIDGET_H
