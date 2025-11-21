#include "contextmanagerdialog.h"
#include "ui_contextmanagerdialog.h"
#include <QMessageBox>

ContextManagerDialog::ContextManagerDialog(LinkManager* manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContextManagerDialog),
    m_manager(manager)
{
    ui->setupUi(this);
    loadContexts();
}

ContextManagerDialog::~ContextManagerDialog()
{
    delete ui;
}

void ContextManagerDialog::loadContexts()
{
    ui->contextListWidget->clear();
    const std::vector<std::string>& contexts = m_manager->getContexts();
    for (const std::string& c : contexts) {
        ui->contextListWidget->addItem(QString::fromStdString(c));
    }
}

void ContextManagerDialog::on_addContextButton_clicked()
{
    QString newName = ui->newContextLineEdit->text().trimmed();
    if (newName.isEmpty()) return;

    std::string nameStd = newName.toStdString();
    if (m_manager->hasContext(nameStd)) {
        QMessageBox::warning(this, "Помилка", "Такий контекст вже існує!");
        return;
    }

    m_manager->addContext(nameStd);
    loadContexts();
    ui->newContextLineEdit->clear();
}

void ContextManagerDialog::on_deleteContextButton_clicked()
{
    QListWidgetItem* selected = ui->contextListWidget->currentItem();
    if (!selected) return;

    m_manager->removeContext(selected->text().toStdString());
    loadContexts();
}
