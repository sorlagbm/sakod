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

private:
    Ui::MainWindow *ui;
    QFile* workFile;
    stw studentList;
    vector<Date> taskList;
    ConnectedList<QTableWidget*> windowList;
    QStringList Clabels;
    QStringList Rlabels;
};
#endif // MAINWINDOW_H
