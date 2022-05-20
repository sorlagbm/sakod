#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTableWidget>
#include <QMessageBox>
#include "student.h"
#include <map>
#include "connectedlist\ConnectedList.h"
#include "task.h"
#include <vector>
#include <QInputDialog>
#include <QCalendarWidget>
#include <QListWidgetItem>
#include <algorithm>
#include <QFileDialog>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    using stw = map<int, vector<student>>;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_actionAdd_group_triggered();

    void on_actionAdd_task_triggered();

    void on_actionAdd_date_triggered();

    void on_actionAdd_Student_triggered();

    void on_actionDelete_Group_triggered();

    void on_actionVisit_Sort_triggered();

    void on_actionName_Sort_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionNew_FIle_triggered();

    void on_actionOpen_File_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QFile* workFile;
    vector<vector<QStringList>> field;
    vector<stw> studentList;
    vector<vector<student>> studentLab;
    vector<vector<Date>> taskList;
    vector<QTableWidget*> windowList;
    vector<QStringList> Clabels;
    vector<QStringList> Rlabels;
};
#endif // MAINWINDOW_H
