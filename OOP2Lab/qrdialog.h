/**
 * @file qrdialog.h
 * @brief Заголовочний файл діалогового вікна для відображення QR-коду.
 */

#ifndef QRDIALOG_H
#define QRDIALOG_H

#include <QDialog>
#include <string>

namespace Ui {
class QRDialog;
}

/**
 * @class QRDialog
 * @brief Діалогове вікно для генерації та показу QR-коду.
 *
 * Використовує бібліотеку qrcodegen для створення матриці QR-коду
 * та відмальовує її на віджеті QLabel.
 */
class QRDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор діалогового вікна.
     * @param parent Батьківський віджет (за замовчуванням nullptr).
     */
    explicit QRDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор.
     */
    ~QRDialog();

    /**
     * @brief Генерує QR-код із заданого тексту та відображає його.
     *
     * Метод використовує бібліотеку Nayuki QR Code generator для створення
     * об'єкта QrCode, а потім малює його попіксельно на QImage.
     *
     * @param text Текст (або URL) для кодування.
     */
    void generateQR(const std::string& text);

private:
    Ui::QRDialog *ui; ///< Вказівник на UI об'єкт.
};

#endif // QRDIALOG_H
