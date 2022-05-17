#include "mainwindow.h"
#include "ui_mainwindow.h"

int student::readFromFile(const std::string& FileName){
    QFile* inputFile = new QFile(FileName.c_str());
    inputFile->open(QIODevice::ReadOnly);
    if(inputFile->size() != 0){
        inputFile->write((char*)&this->groupNumber, sizeof(this->groupNumber));
        inputFile->write((char*)&this->isInGroup, sizeof(this->isInGroup));

        unsigned buffer = this->surname.size() + 1;
        inputFile->write((char*)&buffer, sizeof(buffer));
        inputFile->write(this->surname.c_str(), buffer);

        inputFile->close();
        return 0;
    }
    inputFile->close();
    return -1;
}

int student::writeToFile(const std::string& FileName){
    this->surname = "";
    this->groupNumber = -1;
    this->isInGroup = false;

    QFile* outputFile = new QFile(FileName.c_str());
    outputFile->open(QIODevice::WriteOnly);

    outputFile->read((char*)&this->groupNumber, sizeof(this->groupNumber));
    outputFile->read((char*)&this->isInGroup, sizeof(this->isInGroup));

    unsigned buffer = 0;
    outputFile->write((char*)&buffer, sizeof(buffer));
    char* bufstr = new char[buffer + 1];
    outputFile->write(bufstr, buffer);
    this->surname = bufstr;
    delete[] bufstr;

    outputFile->close();
    return 0;
}

int Task::readFromFile(const std::string& FileName){
    QFile* inputFile = new QFile(FileName.c_str());
    inputFile->open(QIODevice::ReadOnly);
    if(inputFile->size() != 0){
        inputFile->write((char*)&this->date.day, sizeof(this->date.day));
        inputFile->write((char*)&this->date.month, sizeof(this->date.month));
        inputFile->write((char*)&this->date.year, sizeof(this->date.year));

        unsigned buffer = this->name.size() + 1;
        inputFile->write((char*)&buffer, sizeof(buffer));
        inputFile->write(this->name.c_str(), buffer);

        inputFile->close();
        return 0;
    }
    inputFile->close();
    return -1;
}

int Task::writeToFile(const std::string& FileName){
    this->date.day = 0;
    this->date.month = 0;
    this->date.year = 0;

    QFile* outputFile = new QFile(FileName.c_str());
    outputFile->open(QIODevice::WriteOnly);

    outputFile->write((char*)&this->date.day, sizeof(this->date.day));
    outputFile->write((char*)&this->date.month, sizeof(this->date.month));
    outputFile->write((char*)&this->date.year, sizeof(this->date.year));

    unsigned buffer = this->name.size() + 1;
    outputFile->write((char*)&buffer, sizeof(buffer));
    outputFile->write(this->name.c_str(), buffer);

    outputFile->close();

    outputFile->close();
    return 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_pushButton_clicked(){

}

void MainWindow::on_actionAdd_group_triggered(){
    if(this->windowList.isEmpty()) return;
    QString groupNumber = QInputDialog::getText(this, tr("Add Group"),
                                tr("Number:"), QLineEdit::Normal,
                                "", new bool());
    if(groupNumber.isEmpty()) return;
    int n = groupNumber.toUInt();
    auto search = this->studentList.find(n);
    if(search == this->studentList.end()){
        this->studentList.insert({n, vector<student>()});
        ui->listWidget->addItem(groupNumber);
    }
    else{
        QMessageBox::information(this, "Error", "This Group Has Beed Added Previosly");
    }

}


void MainWindow::on_actionAdd_task_triggered(){
    QTableWidget* window = new QTableWidget(0, 0);
    window->setColumnCount(0);
    QString task = QInputDialog::getText(this, tr("Add Task"),
                                tr("Task:"), QLineEdit::Normal,
                                "", new bool());
    if(task.isEmpty()) return;
    this->windowList.insertAfter(new Node<QTableWidget*>(window));
    this->windowList._next();
    ui->tabWidget->addTab(window, task);
    ui->tabWidget->setCurrentWidget(window);
}


void MainWindow::on_actionAdd_date_triggered(){
    if(this->windowList.isEmpty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    QString dateStr = QInputDialog::getText(this, tr("Add Date"),
                                tr("Date (dd/MM/yyyy):"), QLineEdit::Normal,
                                "", new bool());
    if(dateStr.isEmpty()) return;
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    this->taskList.push_back(Date(date.day(), date.month(), date.year()));
    window->setColumnCount(window->columnCount() + 1);
    Clabels.push_back(dateStr);
    window->setHorizontalHeaderLabels(Clabels);
}


void MainWindow::on_actionAdd_Student_triggered(){
    if(this->windowList.isEmpty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    QString name = QInputDialog::getText(this, tr("Add Student"),
                                tr("Name:"), QLineEdit::Normal,
                                "", new bool());
    QString groupNumber = QInputDialog::getText(this, tr("Group Number"),
                                tr("Number:"), QLineEdit::Normal,
                                "", new bool());
    if(name.isEmpty() && groupNumber.isEmpty()) return;
    int n = groupNumber.toUInt();
    //this->studentList.push_back(student(name.toStdString(), n > 0 ? true : false, n));
    auto search = this->studentList.find(n);
    if(search == this->studentList.end()){
        this->studentList.insert({n, vector<student>()});
        ui->listWidget->addItem(groupNumber);
    }
    else{
        search->second.push_back(student(name.toStdString(), true, n));
    }
    window->setRowCount(window->rowCount() + 1);
    Rlabels.push_back(name + '(' + groupNumber + ')');
    window->setVerticalHeaderLabels(Rlabels);
}

