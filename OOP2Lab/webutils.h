#ifndef WEBUTILS_H
#define WEBUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/**
 * @brief Клас для асинхронної роботи з мережею.
 * * Забезпечує функціонал для завантаження даних з інтернету,
 * зокрема для отримання HTML-заголовків веб-сторінок без блокування графічного інтерфейсу (UI).
 */
class WebUtils : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класу WebUtils.
     * @param parent Батьківський об'єкт (за замовчуванням nullptr).
     */
    explicit WebUtils(QObject *parent = nullptr);

    /**
     * @brief Асинхронно отримує заголовок (<title>) веб-сторінки.
     * * Функція ініціює HTTP GET запит у фоновому режимі. Після успішного
     * завантаження або виникнення помилки об'єкт випустить сигнал titleReady().
     * * @param url Рядок з URL-адресою веб-сторінки.
     */
    void fetchTitleAsync(const QString& url);

signals:
    /**
     * @brief Сигнал, що випускається по завершенню мережевого запиту.
     * @param url Оригінальний URL, на який відправлявся запит.
     * @param title Знайдений заголовок сторінки (або сам URL, якщо заголовок не знайдено).
     */
    void titleReady(const QString& url, const QString& title);

private slots:
    /**
     * @brief Внутрішній слот для обробки мережевої відповіді.
     * @param reply Вказівник на об'єкт відповіді сервера (QNetworkReply).
     */
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *netManager; ///< Вказівник на менеджер мережевих з'єднань Qt.
};

#endif // WEBUTILS_H
