#ifndef QRDIALOG_H
#define QRDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class QRDialog;
}

class QRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRDialog(QWidget *parent = nullptr);
    ~QRDialog();

    void generateQR(const std::string& text);

private:
    Ui::QRDialog *ui;
};

#endif // QRDIALOG_H
