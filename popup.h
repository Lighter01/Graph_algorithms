#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDoubleValidator>


class MyDialog : public QDialog
{
public:
    MyDialog(QWidget* parent = nullptr) : QDialog(parent)
    {
        this->setWindowTitle(" ");
        this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);

        // create a layout for the dialog
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* instruction = new QLabel("Введите вес ребра", this);
        layout->addWidget(instruction);

        // create a text input field
        QLineEdit* inputField = new QLineEdit(this);
        QDoubleValidator* validator = new QDoubleValidator(this);
        inputField->setValidator(validator);
        layout->addWidget(inputField);

        // create a button to close the dialog
        QPushButton* okButton = new QPushButton(tr("OK"), this);
        okButton->setEnabled(false);
        connect(inputField, &QLineEdit::textChanged, [=]() {
            okButton->setEnabled(!inputField->text().isEmpty());
        });

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        layout->addWidget(okButton);

        // set the layout for the dialog
        setLayout(layout);

        // center the dialog on the parent window
        if (parent != nullptr) {
            QPoint center = parent->geometry().center();
            move(center.x() - width() / 2, center.y() - height() / 2);
        }
    }

    QString getValue() const
    {
        QLineEdit* inputField = findChild<QLineEdit*>();
        return inputField->text();
    }
};

#endif // POPUP_H
