/**
 * @file webutils.h
 * @brief Заголовочний файл утиліти для асинхронної роботи з мережею.
 */

#ifndef WEBUTILS_H
#define WEBUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/**
 * @brief Клас WebUtils є допоміжною утилітою для роботи з мережею.
 *
 * Цей клас забезпечує функціонал для виконання асинхронних HTTP-запитів,
 * використовуючи модуль Qt Network. Його основне завдання — завантаження
 * HTML-коду веб-сторінок і парсинг їх заголовків (<title>) у фоновому режимі,
 * що гарантує відсутність блокування головного потоку графічного інтерфейсу (UI).
 */
class WebUtils : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор класу WebUtils.
     * Ініціалізує менеджер мережевих підключень (QNetworkAccessManager).
     * @param parent Вказівник на батьківський об'єкт QObject (за замовчуванням nullptr).
     */
    explicit WebUtils(QObject *parent = nullptr);

    /**
     * @brief Асинхронно отримує заголовок (<title>) веб-сторінки за URL.
     * * Функція ініціює HTTP GET запит. Оскільки запит асинхронний, метод
     * завершується миттєво. Після успішного завантаження сторінки або
     * виникнення мережевої помилки клас генерує сигнал titleReady().
     * * @param url Рядок із повною URL-адресою веб-сторінки (наприклад, "https://google.com").
     */
    void fetchTitleAsync(const QString& url);

signals:
    /**
     * @brief Сигнал, що випромінюється після завершення мережевого запиту.
     * Цей сигнал можна підключити до слота в UI (наприклад, у AddLinkDialog),
     * щоб автоматично заповнити поле назви посилання.
     * * @param url Оригінальний URL, на який відправлявся запит.
     * @param title Знайдений заголовок сторінки (якщо заголовок відсутній або сталася помилка — повертається сам URL).
     */
    void titleReady(const QString& url, const QString& title);

private slots:
    /**
     * @brief Внутрішній слот для обробки завершення мережевої відповіді.
     * Викликається автоматично, коли QNetworkAccessManager закінчує завантаження даних.
     * Зчитує отриманий HTML, знаходить тег <title> та випускає сигнал titleReady.
     * * @param reply Вказівник на об'єкт відповіді сервера (QNetworkReply).
     */
    void onReplyFinished(QNetworkReply *reply);

private:
    /**
     * @brief Вказівник на менеджер мережевих з'єднань Qt, що відповідає за диспетчеризацію запитів.
     */
    QNetworkAccessManager *netManager;
};

#endif // WEBUTILS_H
