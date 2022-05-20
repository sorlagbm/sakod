#include "mainwindow.h"
#include "ui_mainwindow.h"

int student::writeToFile(const std::string& FileName){
    QFile* inputFile = new QFile(FileName.c_str());
    inputFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(inputFile->size() != 0){
        inputFile->write((char*)&this->groupNumber, sizeof(this->groupNumber));
        inputFile->write((char*)&this->isInGroup, sizeof(this->isInGroup));
        inputFile->write((char*)&this->wasCount, sizeof(this->wasCount));
        unsigned buffer = this->surname.size() + 1;
        inputFile->write((char*)&buffer, sizeof(buffer));
        inputFile->write(this->surname.c_str(), buffer);

        inputFile->close();
        return 0;
    }
    inputFile->close();
    return -1;
}

int student::readFromFile(const std::string& FileName){

    QFile* outputFile = new QFile(FileName.c_str());
    outputFile->open(QIODevice::ReadOnly);

    outputFile->read((char*)&this->groupNumber, sizeof(this->groupNumber));
    outputFile->read((char*)&this->isInGroup, sizeof(this->isInGroup));
    outputFile->read((char*)&this->wasCount, sizeof(this->wasCount));
    unsigned buffer = 0;
    outputFile->read((char*)&buffer, sizeof(buffer));
    char* bufstr = new char[buffer + 1];
    outputFile->read(bufstr, buffer);
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
    workFile = nullptr;

}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_pushButton_clicked(){
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    QAbstractItemModel* model = window->model();
    QString date = QInputDialog::getText(this, tr("Date"),
                                tr("Date:"), QLineEdit::Normal,
                                "", new bool());
    unsigned n = 0;
    if (window->columnCount() == 1){
        QVariant v = model->headerData(0/*номер столбца, или строки*/,
                                  Qt::Horizontal /*или Qt::Vertical*/,
                                  Qt::DisplayRole);
        QString hlabel = v.toString();
        if(hlabel == date) n = 0;
        else{
            QMessageBox::information(this, "Error", "Error");
            return;
        }
    }
    for(auto i = 0; i < window->columnCount(); ++i){
        QVariant v = model->headerData(i/*номер столбца, или строки*/,
                                  Qt::Horizontal /*или Qt::Vertical*/,
                                  Qt::DisplayRole);
        QString hlabel = v.toString();
        if(hlabel == date) n = i;
    }  
    for(auto i = 0; i < window->rowCount(); ++i){
        if(window->item(i, n) == 0){
            QMessageBox::information(this, "Error", "Empty Field");
            return;
        }
    }
    QListWidget* out = new QListWidget();
    out->show();
    for(auto i = 0; i < window->rowCount(); ++i){
        //stw::iterator sw = this->studentList.begin();
        if(window->item(i, n)->text() == 'A') out->addItem(this->Rlabels[ui->tabWidget->currentIndex()][i]);
        if(window->item(i, n)->text() == 'F') continue;
    }
}

void MainWindow::on_actionAdd_group_triggered(){
    if(this->windowList.empty()) return;
    QString groupNumber = QInputDialog::getText(this, tr("Add Group"),
                                tr("Number:"), QLineEdit::Normal,
                                "", new bool());
    if(groupNumber.isEmpty()) return;
    int n = groupNumber.toUInt();
    auto search = this->studentList[ui->tabWidget->currentIndex()].find(n);
    if(search == this->studentList[ui->tabWidget->currentIndex()].end()){
        this->studentList[ui->tabWidget->currentIndex()].insert({n, vector<student>()});
        //ui->listWidget->addItem(groupNumber);
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
    this->windowList.push_back(window);
    //this->windowList._next();
    ui->tabWidget->addTab(window, task);
    ui->tabWidget->setCurrentWidget(window);
    this->studentList.push_back(stw());
    this->studentLab.push_back(vector<student>());
    this->taskList.push_back(vector<Date>());
    this->Rlabels.push_back(QStringList());
    this->Clabels.push_back(QStringList());
    //ui->listWidget->clear();
}


void MainWindow::on_actionAdd_date_triggered(){
    if(this->windowList.empty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    QString dateStr = QInputDialog::getText(this, tr("Add Date"),
                                tr("Date (dd/MM/yyyy):"), QLineEdit::Normal,
                                "", new bool());
    if(dateStr.isEmpty()) return;
    QDate date = QDate::fromString(dateStr, "dd/MM/yyyy");
    this->taskList[ui->tabWidget->currentIndex()].push_back(Date(date.day(), date.month(), date.year()));
    window->setColumnCount(window->columnCount() + 1);
    Clabels[ui->tabWidget->currentIndex()].push_back(dateStr);
    //qDebug() << Clabels;
    window->setHorizontalHeaderLabels(Clabels[ui->tabWidget->currentIndex()]);

}


void MainWindow::on_actionAdd_Student_triggered(){
    if(this->windowList.empty()) return;
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
    auto search = this->studentList[ui->tabWidget->currentIndex()].find(n);
    if(search == this->studentList[ui->tabWidget->currentIndex()].end()){
        this->studentList[ui->tabWidget->currentIndex()].insert({n, vector<student>()});
        //ui->listWidget->addItem(groupNumber);
        auto i = prev(this->studentList[ui->tabWidget->currentIndex()].end(), 1);
        i->second.push_back(student(name.toStdString(), true, n));
    }
    else{
        search->second.push_back(student(name.toStdString(), true, n));
    }
    window->setRowCount(window->rowCount() + 1);
    this->studentLab[ui->tabWidget->currentIndex()].push_back(student(QString(name + '(' + groupNumber + ')').toStdString(), n > 0 ? true : false, n > 0 ? n : 0));
    Rlabels[ui->tabWidget->currentIndex()].push_back(name + '(' + groupNumber + ')');
    window->setVerticalHeaderLabels(Rlabels[ui->tabWidget->currentIndex()]);
}


void MainWindow::on_actionDelete_Group_triggered(){
    if(this->windowList.empty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    QString groupNumber = QInputDialog::getText(this, tr("Group Number"),
                                tr("Number:"), QLineEdit::Normal,
                                "", new bool());
    if(groupNumber.isEmpty()) return;
    int n = groupNumber.toUInt();
    unsigned number = 0;
    //for(auto i = 0; i < ui->listWidget->count(); ++i){
        //(groupNumber == ui->listWidget->item(i)->text()) { number = i; break; }
     //}
    auto search = this->studentList[ui->tabWidget->currentIndex()].find(n);
    if(search == this->studentList[ui->tabWidget->currentIndex()].end()){
        QMessageBox::information(this, "Error", "Group hasn't been find");
        return;
    }
    else{
        QStringList a;
        for(auto i = 0; i < Rlabels.size(); i++){
            if(this->studentLab[ui->tabWidget->currentIndex()][i].groupNumber != n){
                //Rlabels.erase(Rlabels.begin() + i);
                a[ui->tabWidget->currentIndex()].push_back(Rlabels[ui->tabWidget->currentIndex()][i]);
                //this->studentLab.erase(this->studentLab.begin() + i);

            }
            //i = 0;
        }
        Rlabels[ui->tabWidget->currentIndex()].clear();
        Rlabels[ui->tabWidget->currentIndex()] = a;
        window->clear();
        this->studentList[ui->tabWidget->currentIndex()].erase(search);
        //delete ui->listWidget->takeItem(number);
        window->setRowCount(Rlabels[ui->tabWidget->currentIndex()].size());
        window->setVerticalHeaderLabels(Rlabels[ui->tabWidget->currentIndex()]);
    }
}

void MainWindow::on_actionVisit_Sort_triggered(){
    if(this->windowList.empty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    auto n = 0;
    for(auto i = 0; i < window->rowCount(); ++i){
        n = 0;
        for(auto j = 0; j < window->columnCount(); ++j){
            if(window->item(i, j)->text() == 'A') n += 1;
        }
        this->studentLab[ui->tabWidget->currentIndex()][i].wasCount = n;
        qDebug() << this->studentLab[i][ui->tabWidget->currentIndex()].wasCount;
    }
    for(auto i = 0; i < window->rowCount(); ++i){
        for(auto j = 0; j < window->columnCount(); ++j){
            if (this->studentLab[j][ui->tabWidget->currentIndex()].wasCount < this->studentLab[ui->tabWidget->currentIndex()][j + 1].wasCount) {
                auto temp = this->studentLab[ui->tabWidget->currentIndex()][j];
                this->studentLab[ui->tabWidget->currentIndex()][j] = this->studentLab[ui->tabWidget->currentIndex()][j + 1];
                this->studentLab[ui->tabWidget->currentIndex()][j + 1] = temp;

            }
        }
    }
    Rlabels.clear();
    for(auto i = 0; i < this->studentLab[ui->tabWidget->currentIndex()].size(); ++i){
        Rlabels[ui->tabWidget->currentIndex()].push_back(QString::fromStdString(this->studentLab[ui->tabWidget->currentIndex()][i].surname));
    }
    window->setRowCount(Rlabels[ui->tabWidget->currentIndex()].size());
    window->setVerticalHeaderLabels(Rlabels[ui->tabWidget->currentIndex()]);
}

void MainWindow::on_actionName_Sort_triggered(){
    if(this->windowList.empty()) return;
    QTableWidget* window = (QTableWidget*)ui->tabWidget->currentWidget();
    std::sort(Rlabels[ui->tabWidget->currentIndex()].begin(), Rlabels[ui->tabWidget->currentIndex()].end());
    std::sort(this->studentLab[ui->tabWidget->currentIndex()].begin(), this->studentLab[ui->tabWidget->currentIndex()].end());
    window->setVerticalHeaderLabels(Rlabels[ui->tabWidget->currentIndex()]);
    for(auto it = this->studentList[ui->tabWidget->currentIndex()].begin(); it != this->studentList[ui->tabWidget->currentIndex()].end(); ++it){
        std::sort(it->second.begin(), it->second.end());
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item){
    QListWidget* out = new QListWidget();
    out->show();
    auto search = this->studentList[ui->tabWidget->currentIndex()].find(item->text().toUInt());
    for(auto i = 0; i < search->second.size(); ++i){
        //stw::iterator sw = this->studentList.begin();
        out->addItem(QString::fromStdString(search->second[i].surname));
    }
}


void MainWindow::on_actionNew_FIle_triggered(){
    this->windowList.clear();
    this->studentList.clear();
    this->studentLab.clear();
    this->taskList.clear();
    this->Rlabels.clear();
    this->Clabels.clear();
    //ui->listWidget->clear();
    ui->tabWidget->clear();
    this->workFile = nullptr;
}


void MainWindow::on_actionOpen_File_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, "*.bin");
    this->workFile = new QFile(fileName);
    this->workFile->open(QIODevice::ReadOnly);

    this->windowList.clear();
    this->studentList.clear();
    this->studentLab.clear();
    this->taskList.clear();
    this->Rlabels.clear();
    this->Clabels.clear();
    //ui->listWidget->clear();
    ui->tabWidget->clear();

    int buffer = 0;
    char* bufstr = new char();
    int tabcount = 0;
    this->workFile->read((char*) &tabcount, sizeof(int));

    for(auto i = 0; i < tabcount; ++i){



        buffer = 0;
        this->workFile->read((char*)&buffer, sizeof(buffer));
        bufstr = new char[buffer + 1];
        this->workFile->read(bufstr, buffer);
        QString tabName = bufstr;
        //this->surname = bufstr;
        qDebug() << tabName;
        //delete[] bufstr;

        QTableWidget* window = new QTableWidget(0, 0);
        ui->tabWidget->addTab(window, tabName);
        this->windowList.push_back(window);
        this->studentList.push_back(stw());
        this->studentLab.push_back(vector<student>());
        this->taskList.push_back(vector<Date>());
        this->Rlabels.push_back(QStringList());
        this->Clabels.push_back(QStringList());
        //ui->listWidget->clear();
        //ui->tabWidget->clear();

        int cCount = 0;
        this->workFile->read((char*)& cCount, sizeof(cCount));
        for(auto j = 0; j < cCount; j++){
            buffer = 0;
            this->workFile->read((char*)&buffer, sizeof(buffer));
            bufstr = new char[buffer + 1];
            this->workFile->read(bufstr, buffer);
            QString clName = bufstr;
            //this->surname = bufstr;
            qDebug() << clName;
            this->Clabels[i].push_back(clName);
        }

        int rCount = 0;
        this->workFile->read((char*)& rCount, sizeof(rCount));
        for(auto j = 0; j < rCount; j++){
            buffer = 0;
            this->workFile->read((char*)&buffer, sizeof(buffer));
            bufstr = new char[buffer + 1];
            this->workFile->read(bufstr, buffer);
            QString rlName = bufstr;
            //this->surname = bufstr;
            qDebug() << rlName;
            this->Rlabels[i].push_back(rlName);
        }

        int tlCount = 0;
        this->workFile->read((char*)&tlCount, sizeof(tlCount));
        for(auto j = 0; j < tlCount; j++){

            int day, month, year;
            this->workFile->read((char*)&day, sizeof(day));
            this->workFile->read((char*)&month, sizeof(month));
            this->workFile->read((char*)&year, sizeof(year));
            qDebug() << day << month << year;
            this->taskList[i].push_back(Date(day, month, year));

        }

        int slCount = 0;
        this->workFile->read((char*)&slCount, sizeof(slCount));
        for(auto j = 0; j < slCount; ++j){
            int gN, iG, wC;
            string Surname;
            gN = 0;
            iG = 0;
            wC = 0;
            Surname = "";
            this->workFile->read((char*)&gN, sizeof(gN));
            this->workFile->read((char*)&iG, sizeof(iG));
            this->workFile->read((char*)&wC, sizeof(wC));
            buffer = 0;
            qDebug() << gN << iG << wC;
            this->workFile->read((char*)&buffer, sizeof(buffer));
            bufstr = new char[buffer + 1];
            this->workFile->read(bufstr, buffer);
            Surname = bufstr;
            //this->surname = bufstr;
            qDebug() << QString::fromStdString(Surname);
            this->studentLab[i].push_back(student(Surname, iG, gN));
            this->studentLab[i][j].wasCount = wC;

            auto search = this->studentList[i].find(this->studentLab[i][j].groupNumber);
            if(search == this->studentList[i].end()){
                this->studentList[ui->tabWidget->currentIndex()].insert({this->studentLab[i][j].groupNumber, vector<student>()});
                //ui->listWidget->addItem(groupNumber);
                auto e = prev(this->studentList[i].end(), 1);
                e->second.push_back(this->studentLab[i][j]);
            }
            else{
                search->second.push_back(this->studentLab[i][j]);
            }

        }

        window->setRowCount(this->Rlabels[i].size());
        window->setVerticalHeaderLabels(this->Rlabels[i]);
        window->setColumnCount(this->Clabels[i].size());
        window->setHorizontalHeaderLabels(this->Clabels[i]);
    }

    this->workFile->close();
}


void MainWindow::on_actionSave_triggered(){
    if(this->workFile == nullptr){

        QString fileName = QFileDialog::getSaveFileName(this, "*.bin");
        this->workFile = new QFile(fileName);
        this->workFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
        int buffer = 0;

        //Записать сюда сетку
        int h = ui->tabWidget->count();
        this->workFile->write((char*) &h, sizeof(h));

        for(auto i = 0; i < ui->tabWidget->count(); ++i){

            buffer = ui->tabWidget->tabText(i).size() + 1;
            this->workFile->write((char*)&buffer, sizeof(buffer));
            this->workFile->write(ui->tabWidget->tabText(i).toStdString().c_str(), buffer);

            int cCount = this->Clabels[i].size();
            this->workFile->write((char*)&cCount, sizeof(cCount));
            for(auto j = 0; j < cCount; j++){

                buffer = this->Clabels[i][j].size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(this->Clabels[i][j].toStdString().c_str(), buffer);

            }

            int rCount = this->Rlabels[i].size();
            this->workFile->write((char*)&rCount, sizeof(rCount));
            for(auto j = 0; j < rCount; j++){

                buffer = this->Rlabels[i][j].size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(this->Rlabels[i][j].toStdString().c_str(), buffer);

            }

            int tlCount = this->taskList[i].size();
            this->workFile->write((char*)&tlCount, sizeof(tlCount));
            for(auto j = 0; j < tlCount; j++){

                this->workFile->write((char*)&this->taskList[i][j].day, sizeof(this->taskList[i][j].day));
                this->workFile->write((char*)&this->taskList[i][j].month, sizeof(this->taskList[i][j].month));
                this->workFile->write((char*)&this->taskList[i][j].year, sizeof(this->taskList[i][j].year));

            }

            int slCount = this->studentLab[i].size();
            this->workFile->write((char*)&slCount, sizeof(slCount));
            for(auto j = 0; j < slCount; ++j){
                int gN, iG, wC;
                string Surname;
                gN = this->studentLab[i][j].groupNumber;
                iG = this->studentLab[i][j].isInGroup;
                wC = this->studentLab[i][j].wasCount;
                Surname = this->studentLab[i][j].surname;
                this->workFile->write((char*)&gN, sizeof(gN));
                this->workFile->write((char*)&iG, sizeof(iG));
                this->workFile->write((char*)&wC, sizeof(wC));
                buffer = Surname.size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(Surname.c_str(), buffer);



            }



        }

        this->workFile->close();
    }
    else{
        this->workFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
        int buffer = 0;

        //Записать сюда сетку
        int h = ui->tabWidget->count();
        this->workFile->write((char*) &h, sizeof(h));

        for(auto i = 0; i < ui->tabWidget->count(); ++i){

            buffer = ui->tabWidget->tabText(i).size() + 1;
            this->workFile->write((char*)&buffer, sizeof(buffer));
            this->workFile->write(ui->tabWidget->tabText(i).toStdString().c_str(), buffer);

            int cCount = this->Clabels[i].size();
            this->workFile->write((char*)&cCount, sizeof(cCount));
            for(auto j = 0; j < cCount; j++){

                buffer = this->Clabels[i][j].size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(this->Clabels[i][j].toStdString().c_str(), buffer);

            }

            int rCount = this->Rlabels[i].size();
            this->workFile->write((char*)&rCount, sizeof(rCount));
            for(auto j = 0; j < rCount; j++){

                buffer = this->Rlabels[i][j].size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(this->Rlabels[i][j].toStdString().c_str(), buffer);

            }

            int tlCount = this->taskList[i].size();
            this->workFile->write((char*)&tlCount, sizeof(tlCount));
            for(auto j = 0; j < tlCount; j++){

                this->workFile->write((char*)&this->taskList[i][j].day, sizeof(this->taskList[i][j].day));
                this->workFile->write((char*)&this->taskList[i][j].month, sizeof(this->taskList[i][j].month));
                this->workFile->write((char*)&this->taskList[i][j].year, sizeof(this->taskList[i][j].year));

            }

            int slCount = this->studentLab[i].size();
            this->workFile->write((char*)&slCount, sizeof(slCount));
            for(auto j = 0; j < slCount; ++j){
                int gN, iG, wC;
                string Surname;
                gN = this->studentLab[i][j].groupNumber;
                iG = this->studentLab[i][j].isInGroup;
                wC = this->studentLab[i][j].wasCount;
                Surname = this->studentLab[i][j].surname;
                this->workFile->write((char*)&gN, sizeof(gN));
                this->workFile->write((char*)&iG, sizeof(iG));
                this->workFile->write((char*)&wC, sizeof(wC));
                buffer = Surname.size() + 1;
                this->workFile->write((char*)&buffer, sizeof(buffer));
                this->workFile->write(Surname.c_str(), buffer);



            }



        }

        this->workFile->close();
    }
}

