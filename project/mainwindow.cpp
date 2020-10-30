#include "mainwindow.h"
#include "ui_mainwindow.h"
#import "main.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_1_stateChanged(int arg1)
{

    QString a = ui->lineEdit_x0->text();
    double x0 = a.toDouble();
    a = ui->lineEdit_y0->text();
    double y0 = a.toDouble();
    a = ui->lineEdit_X->text();
    double X = a.toDouble();
    a = ui->lineEdit_N->text();
    int N = a.toInt();

    Solutions nm = {x0, y0, X, N};
    nm.exact();
    nm.eulerMethod();
    nm.impEulerMethod();
    nm.rungeKuttaMethod();

    ui->plot_solutions->clearGraphs();

    ui->plot_solutions->addGraph();
    ui->plot_solutions->graph(0)->setData(nm.pointsX, nm.pointsYexact);
    QPen Pen0;
    Pen0.setColor(QColor(Qt::blue));
    Pen0.setWidthF(2);
    ui->plot_solutions->graph(0)->setPen(Pen0);

    ui->plot_solutions->addGraph();
    ui->plot_solutions->graph(1)->setData(nm.pointsX, nm.pointsYeuler);
    QPen Pen1;
    Pen1.setColor(QColor(Qt::green));
    Pen1.setWidthF(2);
    ui->plot_solutions->graph(1)->setPen(Pen1);

    ui->plot_solutions->addGraph();
    ui->plot_solutions->graph(2)->setData(nm.pointsX, nm.pointsYimpeuler);
    QPen Pen2;
    Pen2.setColor(QColor(Qt::red));
    Pen2.setWidthF(2);
    ui->plot_solutions->graph(2)->setPen(Pen2);

    ui->plot_solutions->addGraph();
    ui->plot_solutions->graph(3)->setData(nm.pointsX, nm.pointsYrk);
    QPen Pen3;
    Pen3.setColor(QColor(Qt::black));
    Pen3.setWidthF(2);
    ui->plot_solutions->graph(3)->setPen(Pen3);

    ui->plot_solutions->xAxis->setLabel("x");
    ui->plot_solutions->yAxis->setLabel("y");

    double minimum, maximum;
    minimum = maximum = nm.pointsYexact.value(0);

    for (int i = 0; i < N + 1; i++){
        if (nm.pointsYexact.value(i) < minimum)
            minimum = nm.pointsYexact.value(i);
        if (nm.pointsYexact.value(i) > maximum)
            maximum = nm.pointsYexact.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (nm.pointsYeuler.value(i) < minimum)
            minimum = nm.pointsYeuler.value(i);
        if (nm.pointsYeuler.value(i) > maximum)
            maximum = nm.pointsYeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (nm.pointsYimpeuler.value(i) < minimum)
            minimum = nm.pointsYimpeuler.value(i);
        if (nm.pointsYimpeuler.value(i) > maximum)
            maximum = nm.pointsYimpeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (nm.pointsYrk.value(i) < minimum)
            minimum = nm.pointsYrk.value(i);
        if (nm.pointsYrk.value(i) > maximum)
            maximum = nm.pointsYrk.value(i);
    }

    ui->plot_solutions->xAxis->setRange(x0 - 1, X + 1);
    ui->plot_solutions->yAxis->setRange(minimum - 50, maximum + 50);

    ui->plot_solutions->legend->setVisible(true);
    ui->plot_solutions->graph(0)->setName("Exact");
    ui->plot_solutions->graph(1)->setName("Euler");
    ui->plot_solutions->graph(2)->setName("Improved Euler");
    ui->plot_solutions->graph(3)->setName("Runge-Kutta");
    ui->plot_solutions->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    ui->plot_solutions->legend->setBrush(QColor(255, 255, 255, 150));

    ui->plot_solutions->replot();

}

void MainWindow::on_checkBox_ExactSol_stateChanged(int arg1)
{
    if (ui->checkBox_ExactSol->checkState())
        ui->plot_solutions->graph(0)->setVisible(true);
    else
        ui->plot_solutions->graph(0)->setVisible(false);
    ui->plot_solutions->replot();
}

void MainWindow::on_checkBox_EulerSol_stateChanged(int arg1)
{
    if (ui->checkBox_EulerSol->checkState())
        ui->plot_solutions->graph(1)->setVisible(true);
    else
        ui->plot_solutions->graph(1)->setVisible(false);
    ui->plot_solutions->replot();
}

void MainWindow::on_checkBox_ImpeulerSol_stateChanged(int arg1)
{
    if (ui->checkBox_ImpeulerSol->checkState())
        ui->plot_solutions->graph(2)->setVisible(true);
    else
        ui->plot_solutions->graph(2)->setVisible(false);
    ui->plot_solutions->replot();
}

void MainWindow::on_checkBox_RkSol_stateChanged(int arg1)
{
    if (ui->checkBox_RkSol->checkState())
        ui->plot_solutions->graph(3)->setVisible(true);
    else
        ui->plot_solutions->graph(3)->setVisible(false);
    ui->plot_solutions->replot();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    QString a = ui->lineEdit_x0->text();
    double x0 = a.toDouble();
    a = ui->lineEdit_y0->text();
    double y0 = a.toDouble();
    a = ui->lineEdit_X->text();
    double X = a.toDouble();
    a = ui->lineEdit_N->text();
    int N = a.toInt();

    Errors errors = {x0, y0, X, N};
    errors.findEulerLocalError(N);
    errors.findImpeulerLocalError(N);
    errors.findRkLocalError(N);

    Solutions nm = {x0, y0, X, N};

    ui->plot_localErrors->clearGraphs();

    ui->plot_localErrors->addGraph();
    ui->plot_localErrors->graph(0)->setData(nm.pointsX, errors.leForEuler);
    QPen Pen1;
    Pen1.setColor(QColor(Qt::green));
    Pen1.setWidthF(2);
    ui->plot_localErrors->graph(0)->setPen(Pen1);

    ui->plot_localErrors->addGraph();
    ui->plot_localErrors->graph(1)->setData(nm.pointsX, errors.leForImpeuler);
    QPen Pen2;
    Pen2.setColor(QColor(Qt::red));
    Pen2.setWidthF(2);
    ui->plot_localErrors->graph(1)->setPen(Pen2);

    ui->plot_localErrors->addGraph();
    ui->plot_localErrors->graph(2)->setData(nm.pointsX, errors.leForRk);
    QPen Pen3;
    Pen3.setColor(QColor(Qt::black));
    Pen3.setWidthF(2);
    ui->plot_localErrors->graph(2)->setPen(Pen3);

    ui->plot_localErrors->xAxis->setLabel("x");
    ui->plot_localErrors->yAxis->setLabel("e");

    double minimum, maximum;
    minimum = maximum = errors.leForEuler.value(0);

    for (int i = 0; i < N + 1; i++){
        if (errors.leForEuler.value(i) < minimum)
            minimum = errors.leForEuler.value(i);
        if (errors.leForEuler.value(i) > maximum)
            maximum = errors.leForEuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.leForImpeuler.value(i) < minimum)
            minimum = errors.leForImpeuler.value(i);
        if (errors.leForImpeuler.value(i) > maximum)
            maximum = errors.leForImpeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.leForRk.value(i) < minimum)
            minimum = errors.leForRk.value(i);
        if (errors.leForRk.value(i) > maximum)
            maximum = errors.leForRk.value(i);
    }

    ui->plot_localErrors->xAxis->setRange(x0 - 1, X + 1);
    ui->plot_localErrors->yAxis->setRange(minimum - 5, maximum + 5);

    ui->plot_localErrors->legend->setVisible(true);
    ui->plot_localErrors->graph(0)->setName("Euler");
    ui->plot_localErrors->graph(1)->setName("Improved Euler");
    ui->plot_localErrors->graph(2)->setName("Runge-Kutta");
    ui->plot_localErrors->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    ui->plot_localErrors->legend->setBrush(QColor(255, 255, 255, 150));

    ui->plot_localErrors->replot();
}

void MainWindow::on_checkBox_EulerLe_stateChanged(int arg1)
{
    if (ui->checkBox_EulerLe->checkState())
        ui->plot_localErrors->graph(0)->setVisible(true);
    else
        ui->plot_localErrors->graph(0)->setVisible(false);
    ui->plot_localErrors->replot();
}

void MainWindow::on_checkBox_ImpeulerLe_stateChanged(int arg1)
{
    if (ui->checkBox_ImpeulerLe->checkState())
        ui->plot_localErrors->graph(1)->setVisible(true);
    else
        ui->plot_localErrors->graph(1)->setVisible(false);
    ui->plot_localErrors->replot();
}

void MainWindow::on_checkBox_RkLe_stateChanged(int arg1)
{
    if (ui->checkBox_RkLe->checkState())
        ui->plot_localErrors->graph(2)->setVisible(true);
    else
        ui->plot_localErrors->graph(2)->setVisible(false);
    ui->plot_localErrors->replot();
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    QString a = ui->lineEdit_x0->text();
    double x0 = a.toDouble();
    a = ui->lineEdit_y0->text();
    double y0 = a.toDouble();
    a = ui->lineEdit_X->text();
    double X = a.toDouble();
    a = ui->lineEdit_N->text();
    int N = a.toInt();

    Errors errors = {x0, y0, X, N};
    errors.findEulerGlobalError(N);
    errors.findImpeulerGlobalError(N);
    errors.findRkGlobalError(N);

    Solutions nm = {x0, y0, X, N};

    ui->plot_globalErrors->clearGraphs();

    ui->plot_globalErrors->addGraph();
    ui->plot_globalErrors->graph(0)->setData(nm.pointsX, errors.geForEuler);
    QPen Pen1;
    Pen1.setColor(QColor(Qt::green));
    Pen1.setWidthF(2);
    ui->plot_globalErrors->graph(0)->setPen(Pen1);

    ui->plot_globalErrors->addGraph();
    ui->plot_globalErrors->graph(1)->setData(nm.pointsX, errors.geForImpeuler);
    QPen Pen2;
    Pen2.setColor(QColor(Qt::red));
    Pen2.setWidthF(2);
    ui->plot_globalErrors->graph(1)->setPen(Pen2);

    ui->plot_globalErrors->addGraph();
    ui->plot_globalErrors->graph(2)->setData(nm.pointsX, errors.geForRk);
    QPen Pen3;
    Pen3.setColor(QColor(Qt::black));
    Pen3.setWidthF(2);
    ui->plot_globalErrors->graph(2)->setPen(Pen3);

    ui->plot_globalErrors->xAxis->setLabel("x");
    ui->plot_globalErrors->yAxis->setLabel("e");

    double minimum, maximum;
    minimum = maximum = errors.geForEuler.value(0);

    for (int i = 0; i < N + 1; i++){
        if (errors.geForEuler.value(i) < minimum)
            minimum = errors.geForEuler.value(i);
        if (errors.geForEuler.value(i) > maximum)
            maximum = errors.geForEuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.geForImpeuler.value(i) < minimum)
            minimum = errors.geForImpeuler.value(i);
        if (errors.geForImpeuler.value(i) > maximum)
            maximum = errors.geForImpeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.geForRk.value(i) < minimum)
            minimum = errors.geForRk.value(i);
        if (errors.geForRk.value(i) > maximum)
            maximum = errors.geForRk.value(i);
    }

    ui->plot_globalErrors->xAxis->setRange(x0 - 1, X + 1);
    ui->plot_globalErrors->yAxis->setRange(minimum - 5, maximum + 5);

    ui->plot_globalErrors->legend->setVisible(true);
    ui->plot_globalErrors->graph(0)->setName("Euler");
    ui->plot_globalErrors->graph(1)->setName("Improved Euler");
    ui->plot_globalErrors->graph(2)->setName("Runge-Kutta");
    ui->plot_globalErrors->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    ui->plot_globalErrors->legend->setBrush(QColor(255, 255, 255, 150));

    ui->plot_globalErrors->replot();
}

void MainWindow::on_checkBox_EulerGe_stateChanged(int arg1)
{
    if (ui->checkBox_EulerGe->checkState())
        ui->plot_globalErrors->graph(0)->setVisible(true);
    else
        ui->plot_globalErrors->graph(0)->setVisible(false);
    ui->plot_globalErrors->replot();
}

void MainWindow::on_checkBox_ImpeulerGe_stateChanged(int arg1)
{
    if (ui->checkBox_ImpeulerGe->checkState())
        ui->plot_globalErrors->graph(1)->setVisible(true);
    else
        ui->plot_globalErrors->graph(1)->setVisible(false);
    ui->plot_globalErrors->replot();
}

void MainWindow::on_checkBox_RkGe_stateChanged(int arg1)
{
    if (ui->checkBox_RkGe->checkState())
        ui->plot_globalErrors->graph(2)->setVisible(true);
    else
        ui->plot_globalErrors->graph(2)->setVisible(false);
    ui->plot_globalErrors->replot();
}

void MainWindow::on_checkBox_tg_stateChanged(int arg1)
{
    QString a = ui->lineEdit_x0->text();
    double x0 = a.toDouble();
    a = ui->lineEdit_y0->text();
    double y0 = a.toDouble();
    a = ui->lineEdit_X->text();
    double X = a.toDouble();
    a = ui->lineEdit_N->text();
    int N = a.toInt();
    a = ui->lineEdit_n0->text();
    double n0 = a.toInt();
    a = ui->lineEdit_N_2->text();
    double N1 = a.toInt();

    QVector <double> pointsN;
    for (int i = 0; i < N - n0 + 1; i++)
        pointsN.append(n0 + i);

    Errors errors = {x0, y0, X, N};
    errors.findTotalApproximationGlobalErrors(n0, N1, x0, y0, X);

    ui->plot_totalErrors->clearGraphs();

    ui->plot_totalErrors->addGraph();
    ui->plot_totalErrors->graph(0)->setData(pointsN, errors.maxgeForEuler);
    QPen Pen1;
    Pen1.setColor(QColor(Qt::green));
    Pen1.setWidthF(2);
    ui->plot_totalErrors->graph(0)->setPen(Pen1);

    ui->plot_totalErrors->addGraph();
    ui->plot_totalErrors->graph(1)->setData(pointsN, errors.maxgeForImpeuler);
    QPen Pen2;
    Pen2.setColor(QColor(Qt::red));
    Pen2.setWidthF(2);
    ui->plot_totalErrors->graph(1)->setPen(Pen2);

    ui->plot_totalErrors->addGraph();
    ui->plot_totalErrors->graph(2)->setData(pointsN, errors.maxgeForRk);
    QPen Pen3;
    Pen3.setColor(QColor(Qt::black));
    Pen3.setWidthF(2);
    ui->plot_totalErrors->graph(2)->setPen(Pen3);

    ui->plot_totalErrors->xAxis->setLabel("n");
    ui->plot_totalErrors->yAxis->setLabel("e");

    double minimum, maximum;
    minimum = maximum = errors.maxgeForEuler.value(0);

    for (int i = 0; i < N + 1; i++){
        if (errors.maxgeForEuler.value(i) < minimum)
            minimum = errors.maxgeForEuler.value(i);
        if (errors.maxgeForEuler.value(i) > maximum)
            maximum = errors.maxgeForEuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.maxgeForImpeuler.value(i) < minimum)
            minimum = errors.maxgeForImpeuler.value(i);
        if (errors.maxgeForImpeuler.value(i) > maximum)
            maximum = errors.maxgeForImpeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.maxgeForRk.value(i) < minimum)
            minimum = errors.maxgeForRk.value(i);
        if (errors.maxgeForRk.value(i) > maximum)
            maximum = errors.maxgeForRk.value(i);
    }

    ui->plot_totalErrors->xAxis->setRange(n0 - 1, N1 + 1);
    ui->plot_totalErrors->yAxis->setRange(minimum - 50, maximum + 100);

    ui->plot_totalErrors->legend->setVisible(true);
    ui->plot_totalErrors->graph(0)->setName("Euler");
    ui->plot_totalErrors->graph(1)->setName("Improved Euler");
    ui->plot_totalErrors->graph(2)->setName("Runge-Kutta");
    ui->plot_totalErrors->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);
    ui->plot_totalErrors->legend->setBrush(QColor(255, 255, 255, 150));

    ui->plot_totalErrors->replot();
}

void MainWindow::on_checkBox_EulerTe_stateChanged(int arg1)
{
    if (ui->checkBox_EulerTe->checkState())
        ui->plot_totalErrors->graph(0)->setVisible(true);
    else
        ui->plot_totalErrors->graph(0)->setVisible(false);
    ui->plot_totalErrors->replot();
}

void MainWindow::on_checkBox_ImpeulerTe_stateChanged(int arg1)
{
    if (ui->checkBox_ImpeulerTe->checkState())
        ui->plot_totalErrors->graph(1)->setVisible(true);
    else
        ui->plot_totalErrors->graph(1)->setVisible(false);
    ui->plot_totalErrors->replot();
}

void MainWindow::on_checkBox_RkTe_stateChanged(int arg1)
{
    if (ui->checkBox_RkTe->checkState())
        ui->plot_totalErrors->graph(2)->setVisible(true);
    else
        ui->plot_totalErrors->graph(2)->setVisible(false);
    ui->plot_totalErrors->replot();
}

void MainWindow::on_plot_button_main_clicked()
{
    if (ui->checkBox_1->checkState())
        on_checkBox_1_stateChanged(0);
    if (ui->checkBox_2->checkState())
        on_checkBox_2_stateChanged(1);
    if (ui->checkBox_3->checkState())
        on_checkBox_3_stateChanged(2);
}

void MainWindow::on_checkBox_tg_2_stateChanged(int arg1)
{

    QString a = ui->lineEdit_x0->text();
    double x0 = a.toDouble();
    a = ui->lineEdit_y0->text();
    double y0 = a.toDouble();
    a = ui->lineEdit_X->text();
    double X = a.toDouble();
    a = ui->lineEdit_N->text();
    int N = a.toInt();
    a = ui->lineEdit_n0->text();
    double n0 = a.toInt();
    a = ui->lineEdit_N_2->text();
    double N1 = a.toInt();

    QVector <double> pointsN;
    for (int i = 0; i < N - n0 + 1; i++)
        pointsN.append(n0 + i);

    Errors errors = {x0, y0, X, N};
    errors.findTotalApproximationLocalErrors(n0, N1, x0, y0, X);

    ui->plot_totalErrors_2->clearGraphs();

    ui->plot_totalErrors_2->addGraph();
    ui->plot_totalErrors_2->graph(0)->setData(pointsN, errors.maxleForEuler);
    QPen Pen1;
    Pen1.setColor(QColor(Qt::green));
    Pen1.setWidthF(2);
    ui->plot_totalErrors_2->graph(0)->setPen(Pen1);

    ui->plot_totalErrors_2->addGraph();
    ui->plot_totalErrors_2->graph(1)->setData(pointsN, errors.maxleForImpeuler);
    QPen Pen2;
    Pen2.setColor(QColor(Qt::red));
    Pen2.setWidthF(2);
    ui->plot_totalErrors_2->graph(1)->setPen(Pen2);

    ui->plot_totalErrors_2->addGraph();
    ui->plot_totalErrors_2->graph(2)->setData(pointsN, errors.maxleForRk);
    QPen Pen3;
    Pen3.setColor(QColor(Qt::black));
    Pen3.setWidthF(2);
    ui->plot_totalErrors_2->graph(2)->setPen(Pen3);

    ui->plot_totalErrors_2->xAxis->setLabel("n");
    ui->plot_totalErrors_2->yAxis->setLabel("e");

    double minimum, maximum;
    minimum = maximum = errors.maxleForEuler.value(0);

    for (int i = 0; i < N + 1; i++){
        if (errors.maxleForEuler.value(i) < minimum)
            minimum = errors.maxleForEuler.value(i);
        if (errors.maxleForEuler.value(i) > maximum)
            maximum = errors.maxleForEuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.maxleForImpeuler.value(i) < minimum)
            minimum = errors.maxleForImpeuler.value(i);
        if (errors.maxleForImpeuler.value(i) > maximum)
            maximum = errors.maxleForImpeuler.value(i);
    }
    for (int i = 0; i < N + 1; i++){
        if (errors.maxleForRk.value(i) < minimum)
            minimum = errors.maxleForRk.value(i);
        if (errors.maxleForRk.value(i) > maximum)
            maximum = errors.maxleForRk.value(i);
    }

    ui->plot_totalErrors_2->xAxis->setRange(n0 - 1, N1 + 1);
    ui->plot_totalErrors_2->yAxis->setRange(minimum - 50, maximum + 100);

    ui->plot_totalErrors_2->legend->setVisible(true);
    ui->plot_totalErrors_2->graph(0)->setName("Euler");
    ui->plot_totalErrors_2->graph(1)->setName("Improved Euler");
    ui->plot_totalErrors_2->graph(2)->setName("Runge-Kutta");
    ui->plot_totalErrors_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);
    ui->plot_totalErrors_2->legend->setBrush(QColor(255, 255, 255, 150));

    ui->plot_totalErrors_2->replot();
}

void MainWindow::on_checkBox_EulerTe_2_stateChanged(int arg1)
{
    if (ui->checkBox_EulerTe_2->checkState())
        ui->plot_totalErrors_2->graph(0)->setVisible(true);
    else
        ui->plot_totalErrors_2->graph(0)->setVisible(false);
    ui->plot_totalErrors_2->replot();
}

void MainWindow::on_checkBox_ImpeulerTe_2_stateChanged(int arg1)
{
    if (ui->checkBox_ImpeulerTe_2->checkState())
        ui->plot_totalErrors_2->graph(1)->setVisible(true);
    else
        ui->plot_totalErrors_2->graph(1)->setVisible(false);
    ui->plot_totalErrors_2->replot();
}

void MainWindow::on_checkBox_RkTe_2_stateChanged(int arg1)
{
    if (ui->checkBox_RkTe_2->checkState())
        ui->plot_totalErrors_2->graph(2)->setVisible(true);
    else
        ui->plot_totalErrors_2->graph(2)->setVisible(false);
    ui->plot_totalErrors_2->replot();
}

void MainWindow::on_plot_button4_3_clicked()
{
    if (ui->checkBox_tg->checkState())
        on_checkBox_tg_stateChanged(0);
    if (ui->checkBox_tg_2->checkState())
        on_checkBox_tg_2_stateChanged(1);
}

