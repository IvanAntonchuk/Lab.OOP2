# Лабораторна робота №1b: Моделювання з використанням UML

**Студент:** Антончук Іван Дмитрович (Група ІПС-21)  
**Спеціальність:** 121 Інженерія програмного забезпечення  
**Дисципліна:** Об'єктно-орієнтоване проєктування  
**Варіант:** Code repository (на прикладі GitHub)  

---

## 1. Опис предметної області
**GitHub** — це найбільша у світі веб-платформа для хостингу IT-проєктів та спільної розробки, що базується на системі контролю версій Git. Платформа виконує роль екосистеми, яка об'єднує хмарне сховище коду, соціо-технічні інструменти для колаборації розробників та автоматизовані конвеєри CI/CD.

Архітектура GitHub є високонавантаженою мікросервісною системою, яка забезпечує цілісність даних при мільйонах одночасних запитів. Основними бізнес-процесами є керування версіями (коміти, гілки), аналіз змін (Pull Requests), відстеження дефектів (Issues) та автоматизація життєвого циклу ПЗ (Actions).

*(Детальний технічний опис термінів наведено у файлі `Glossary.md`)*.

---

## 2. UML Моделювання системи

У ході роботи було створено 13 типів діаграм (згідно зі стандартом UML 2.x) для всебічного аналізу платформи. Всі графічні матеріали та вихідні PlantUML коди розміщені у відповідних піддиректоріях папки `UML_Models`.

### 2.1. Структурне моделювання (Static View)

1. **Use Case Diagram** *Відображає ролі користувачів та їхні функціональні можливості в межах платформи.* ![Use Case Diagram](<UML_Models/Use Case Diagram/UseCase (1).png>)

2. **Class Diagram** *Визначає ключові сутності (User, Repository, PR, Branch) та логічні зв'язки між ними.* ![Class Diagram](<UML_Models/Class Diagram/Class (1).png>)

3. **Component Diagram** *Описує фізичну організацію мікросервісів та їхню взаємодію через інтерфейси.* ![Component Diagram](<UML_Models/Component Diagram/Component (1).png>)

4. **Deployment Diagram** *Ілюструє топологію апаратних засобів: від CDN-вузлів до кластерів баз даних.* ![Deployment Diagram](<UML_Models/Deployment Diagram/Deployment (1).png>)

5. **Object Diagram** *Візуалізує конкретний стан системи під час процесу рев'ю Pull Request розробником.* ![Object Diagram](<UML_Models/Object Diagram/Object (1).png>)

6. **Package Diagram** *Показує логічне групування кодової бази GitHub на рівні архітектурних шарів.* ![Package Diagram](<UML_Models/Package Diagram/Package (1).png>)

7. **Composite Structure Diagram** *Деталізує внутрішню архітектуру компонента "Actions Runner" та його точки доступу.* ![Composite Structure Diagram](<UML_Models/Composite Structure Diagram/CompositeStructure (1).png>)

### 2.2. Поведінкове моделювання (Dynamic View)

8. **Activity Diagram** *Моделює бізнес-логіку обробки серверної команди `git push` з урахуванням валідацій.* ![Activity Diagram](<UML_Models/Activity Diagram/Activity (1).png>)

9. **State Machine Diagram** *Описує переходи між станами об'єкта Pull Request протягом його життєвого циклу.* ![State Machine Diagram](<UML_Models/State Machine Diagram/StateMachine (1).png>)

10. **Sequence Diagram** *Показує обмін повідомленнями в часі при проходженні двофакторної автентифікації.* ![Sequence Diagram](<UML_Models/Sequence Diagram/Sequence (1).png>)

11. **Communication Diagram** *Фокусується на структурній організації об'єктів при ініціації CI/CD пайплайну.* ![Communication Diagram](<UML_Models/Communication Diagram/Communication (1).png>)

12. **Interaction Overview Diagram** *Надає високорівневий огляд взаємозв'язків між сценаріями тестування та деплою.* ![Interaction Overview Diagram](<UML_Models/Interaction Overview Diagram/InteractionOverview (1).png>)

13. **Timing Diagram** *Демонструє часові обмеження та зміни станів апаратних ресурсів під час виконання Job.* ![Timing Diagram](<UML_Models/Timing Diagram/Timing (1).png>)

> **Обґрунтування щодо Profile Diagram:** Даний тип діаграми не використовувався, оскільки стандартна метамодель UML 2.x повністю покрила потреби в описі предметної області GitHub без необхідності розширення через кастомні стереотипи.

---

## 3. Проєктування нової функціональності ("Live Architecture Visualizer")

**Проблема:** При рев'ю великих Pull Request-ів розробникам важко оцінити масштаб архітектурних змін (зміна зв'язків між класами, поява нових інтерфейсів) лише за текстом коду.

**Рішення:** Впровадження інструменту **Live Architecture Visualizer**. Цей сервіс автоматично аналізує зміни в ООП-структурі коду (C++, Java, C#) при кожному пуші. 
Система порівнює AST (Abstract Syntax Tree) поточної гілки та `main`, виявляє зміни в ієрархії класів і автоматично генерує архітектурну діаграму, яку публікує як інтерактивний коментар до Pull Request. Це дозволяє рев'юеру миттєво побачити, як зміни вплинули на дизайн системи.

**Логіка роботи нової функції (Activity Diagram):** ![Live Architecture Visualizer](<UML_Models/Live Architecture Visualizer Diagram/Feature_LiveUML.png>)

---
**2026 | Taras Shevchenko National University of Kyiv**
