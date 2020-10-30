#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plot_button_clicked();

    void on_checkBox_ExactSol_stateChanged(int arg1);

    void on_checkBox_EulerSol_stateChanged(int arg1);

    void on_checkBox_ImpeulerSol_stateChanged(int arg1);

    void on_checkBox_RkSol_stateChanged(int arg1);

    void on_plot_button2_clicked();

    void on_checkBox_EulerLe_stateChanged(int arg1);

    void on_checkBox_ImpeulerLe_stateChanged(int arg1);

    void on_checkBox_RkLe_stateChanged(int arg1);

    void on_plot_button3_clicked();

    void on_checkBox_EulerLe_2_stateChanged(int arg1);

    void on_checkBox_ImpeulerGe_stateChanged(int arg1);

    void on_checkBox_RkGe_stateChanged(int arg1);

    void on_checkBox_EulerGe_stateChanged(int arg1);

    void on_plot_button_main_clicked();

    void on_plot_button4_clicked();

    void on_checkBox_EulerTe_stateChanged(int arg1);

    void on_checkBox_ImpeulerTe_stateChanged(int arg1);

    void on_checkBox_RkTe_stateChanged(int arg1);

    void on_checkBox_1_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_plot_button4_2_clicked();

    void on_checkBox_EulerTe_2_stateChanged(int arg1);

    void on_checkBox_ImpeulerTe_2_stateChanged(int arg1);

    void on_checkBox_RkTe_2_stateChanged(int arg1);

    void on_checkBox_tg_stateChanged(int arg1);

    void on_checkBox_tg_2_stateChanged(int arg1);

    void on_plot_button4_3_clicked();

    void on_plot_button_main_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
