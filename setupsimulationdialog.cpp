#include "setupsimulationdialog.h"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>

SetupSimulationDialog::SetupSimulationDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
    , phNumber_{3}
{
    QValidator *validator = new QIntValidator(3, 20, this);
    QLabel *phNumberLabel = new QLabel("Liczba filozofów");
    phNumberEdit_ = new QLineEdit();
    phNumberEdit_->setValidator(validator);

    QHBoxLayout *setupLayout = new QHBoxLayout;

    phNumberLabel->setBuddy(phNumberEdit_);
    setupLayout->addWidget(phNumberLabel);
    setupLayout->addWidget(phNumberEdit_);

    dialogButtoBox_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addSpacing(20);
    mainLayout->addLayout(setupLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(dialogButtoBox_);

    setLayout(mainLayout);


    connect(dialogButtoBox_, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(dialogButtoBox_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int SetupSimulationDialog::getPhNumber()
{
    return phNumber_;
}

void SetupSimulationDialog::accept()
{
    phNumber_ = phNumberEdit_->text().toInt();
    QDialog::accept();
}
