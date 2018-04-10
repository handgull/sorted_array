#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMap>
#include<QVBoxLayout>
#include<QCheckBox>
#include<QImage>
#include<QtWidgets>
#include<QPushButton>
#include<QListWidgetItem>
#include<QDirIterator>
#include<QFileDialog>


QMap<QCheckBox*, QStringList> dict_chk_strs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *lay = new QVBoxLayout;
    QStringList ss;
    QString root = QFileDialog::getExistingDirectory(this, tr("Click on dataset folder"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString path, folder, right_value;
    QDirIterator it(root, QDirIterator::Subdirectories);
    QCheckBox *previousfolder = nullptr;
    lay->addWidget(ui->checkBox);
    while (it.hasNext())
    {
        path = it.next();
        folder = path.split(root.split("/")[root.split("/").length()-1])[1];
        right_value = folder.split("/")[folder.split("/").length()-1];
        if(it.fileInfo().isFile()){
            ss.insert(ss.length(), path);
            continue;
        }
        if(!it.fileInfo().isDir() || right_value == "." || right_value == "..")
            continue;
        QCheckBox *chk = new QCheckBox(folder);
        lay->addWidget(chk);

        dict_chk_strs.insert(previousfolder, ss);
        previousfolder = chk;
        ss.clear();
    }
    dict_chk_strs.insert(previousfolder, ss);

    ui->scrollAreaWidgetContents->setLayout(lay);
    ui->scrollAreaWidgetContents->show();

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(120,120));
    ui->listWidget->setResizeMode(QListWidget::Adjust);

    updateUI();

}

void MainWindow::updateUI(){

    ui->listWidget->clear();

    foreach (QCheckBox *item, dict_chk_strs.keys())
        if(item != nullptr && item->isChecked())
            foreach (QString str, dict_chk_strs.value(item)) {
                QPixmap p(str);
                QPixmap scaled = p.scaled(QSize(120,120), Qt::IgnoreAspectRatio);
                QListWidgetItem *obj = new QListWidgetItem(QIcon(scaled), item->text());
                obj->setStatusTip(str);
                ui->listWidget->addItem(obj);
            }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_stateChanged()
{
    foreach (QCheckBox *item, dict_chk_strs.keys())
        if(item != nullptr)
            item->setChecked(ui->checkBox->isChecked());
    updateUI();
}


void MainWindow::on_pushButton_clicked()
{
    updateUI();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QLabel *qlabel = new QLabel();
    qlabel->setPixmap(QPixmap::fromImage(QImage(item->statusTip())));
    qlabel->show();

}
