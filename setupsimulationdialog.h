#ifndef SETUPSIMULATIONDIALOG_H
#define SETUPSIMULATIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

class QLineEdit;

class SetupSimulationDialog : public QDialog
{
    Q_OBJECT
public:
    SetupSimulationDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    int getPhNumber();

public slots:
    void accept() override;

private:
    QDialogButtonBox *dialogButtoBox_;
    QLineEdit *phNumberEdit_;

    int phNumber_;
};

#endif // SETUPSIMULATIONDIALOG_H
