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
 * Цей клас є частиною графічного інтерфейсу (View) і відповідає за візуалізацію
 * текстових даних (зокрема URL-посилань) у вигляді двовимірного QR-коду.
 * Використовує сторонню бібліотеку qrcodegen для створення матриці коду
 * та відмальовує її у вигляді зображення (QImage) на віджеті QLabel.
 */
class QRDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор діалогового вікна QRDialog.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    explicit QRDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класу QRDialog.
     * Звільняє ресурси, виділені під графічний інтерфейс.
     */
    ~QRDialog();

    /**
     * @brief Генерує QR-код із заданого тексту та відображає його на екрані.
     *
     * Метод використовує бібліотеку Nayuki QR Code generator для створення
     * об'єкта QrCode із заданим рівнем корекції помилок (ECC). Після цього він
     * створює QImage, попіксельно відмальовуючи темні та світлі модулі матриці,
     * масштабує зображення і виводить його в інтерфейс.
     *
     * @param text Текст (або URL-адреса) для кодування у QR-формат.
     */
    void generateQR(const std::string& text);

private:
    /**
     * @brief Вказівник на об'єкт згенерованого графічного інтерфейсу.
     */
    Ui::QRDialog *ui;
};

#endif // QRDIALOG_H
