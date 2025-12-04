#include "qrdialog.h"
#include "ui_qrdialog.h"
#include "qrcodegen.hpp"
#include <QPainter>

using namespace qrcodegen;

QRDialog::QRDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QR Code");
}

QRDialog::~QRDialog()
{
    delete ui;
}

void QRDialog::generateQR(const std::string& text)
{
    QrCode qr = QrCode::encodeText(text.c_str(), QrCode::Ecc::LOW);

    int scale = 10;
    int border = 2;
    int size = qr.getSize();
    int imgSize = (size + border * 2) * scale;

    QImage image(imgSize, imgSize, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (qr.getModule(x, y)) {
                painter.drawRect((x + border) * scale, (y + border) * scale, scale, scale);
            }
        }
    }
    painter.end();

    ui->qrLabel->setPixmap(QPixmap::fromImage(image));

    if (this->width() < 300) {
        this->resize(400, 400);
    }
}
