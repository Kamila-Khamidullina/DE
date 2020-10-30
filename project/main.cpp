#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Function{

public:

    double funct(double x, double y){
        double power = 0.6666667;
        double f = 3 * pow(y, power);
        return f;
    }

};

class Grid{

public:
    double x0, y0, X, h;
    int N;
    QVector <double> pointsX, pointsYeuler, pointsYimpeuler, pointsYrk, pointsYexact;

    Grid(double x0, double y0, double X, int N){
        this->x0 = x0;
        this->y0 = y0;
        this->X = X;
        this->N = N;
        h = (X - x0) / N;

        for (int i = 0; i < N + 1; i++)
            pointsX.append(x0 + h * i);

        pointsYeuler.append(y0);
        pointsYimpeuler.append(y0);
        pointsYrk.append(y0);
        pointsYexact.append(y0);
    }
};

class Solutions : Grid{

public:
    double h;
    int N;
    QVector <double> pointsX, pointsYeuler, pointsYimpeuler, pointsYrk, pointsYexact;

    Solutions(double x0, double y0, double X, int N) : Grid(x0, y0, X, N){
        Grid grid = {x0, y0, X, N};
        pointsX = grid.pointsX;
        pointsYeuler = grid.pointsYeuler;
        pointsYimpeuler = grid.pointsYimpeuler;
        pointsYrk = grid.pointsYrk;
        pointsYexact = grid.pointsYexact;
        this->h = grid.h;
        this->N = grid.N;
    }

    Function f;

    void exact(){
        for (int i = 1; i < N + 1; i++){
            double x = pointsX.value(i);
            pointsYexact.append(pow((x - 1), 3));
        }
    }

    void eulerMethod(){
        for (int i = 1; i < N + 1; i++)
            pointsYeuler.append(pointsYeuler.value(i - 1) + h * f.funct(pointsX.value(i - 1), pointsYeuler.value(i - 1)));
    }

    void impEulerMethod(){
        for (int i = 1; i < N + 1; i++){
            double k1 = f.funct(pointsX.value(i - 1), pointsYimpeuler.value(i - 1));
            double k2 = f.funct(pointsX.value(i), pointsYimpeuler.value(i - 1) + (h * k1));
            pointsYimpeuler.append(pointsYimpeuler.value(i - 1) + h / 2 * (k1 + k2));
        }
    }

    void rungeKuttaMethod(){
        for (int i = 1; i < N + 1; i++){
            double k1 = f.funct(pointsX.value(i - 1), pointsYrk.value(i - 1));
            double k2 = f.funct(pointsX.value(i - 1) + h / 2, pointsYrk.value(i - 1) + h / 2 * k1);
            double k3 = f.funct(pointsX.value(i - 1) + h / 2, pointsYrk.value(i - 1) + h / 2 * k2);
            double k4 = f.funct(pointsX.value(i - 1) + h, pointsYrk.value(i - 1) + h * k3);
            pointsYrk.append(pointsYrk.value(i - 1) + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));

        }
    }
};

class Errors : Solutions{

public:
    QVector <double> pointsX, pointsYeuler, pointsYimpeuler, pointsYrk, pointsYexact;
    QVector <double> leForEuler, leForImpeuler, leForRk, geForEuler, geForImpeuler, geForRk;
    QVector <double> maxgeForEuler, maxgeForImpeuler, maxgeForRk, maxleForEuler, maxleForImpeuler, maxleForRk;

    Errors(double x0, double y0, double X, int N) : Solutions(x0, y0, X, N){
        Solutions points = {x0, y0, X, N};
        points.exact();
        points.eulerMethod();
        points.impEulerMethod();
        points.rungeKuttaMethod();
        pointsX = points.pointsX;
        pointsYeuler = points.pointsYeuler;
        pointsYimpeuler = points.pointsYimpeuler;
        pointsYrk = points.pointsYrk;
        pointsYexact = points.pointsYexact;
    }

    Function f;

    void findEulerLocalError(int n){
        leForEuler.append(0);
        for (int i = 1; i < n + 1; i++)
            leForEuler.append(pointsYexact.value(i) - pointsYexact.value(i - 1) - h * f.funct(pointsX.value(i - 1), pointsYexact.value(i - 1)));
    }

    void findImpeulerLocalError(int n){
        leForImpeuler.append(0);
        for (int i = 1; i < n + 1; i++){
            double k1 = f.funct(pointsX.value(i - 1), pointsYexact.value(i - 1));
            double k2 = f.funct(pointsX.value(i), pointsYexact.value(i - 1) + (h * k1));
            leForImpeuler.append(pointsYexact.value(i) - pointsYexact.value(i - 1) - h / 2 * (k1 + k2));
        }
    }

    void findRkLocalError(int n){
        leForRk.append(0);
        for (int i = 1; i < n + 1; i++){
            double k1 = f.funct(pointsX.value(i - 1), pointsYexact.value(i - 1));
            double k2 = f.funct(pointsX.value(i - 1) + h / 2, pointsYexact.value(i - 1) + h / 2 * k1);
            double k3 = f.funct(pointsX.value(i - 1) + h / 2, pointsYexact.value(i - 1) + h / 2 * k2);
            double k4 = f.funct(pointsX.value(i - 1) + h, pointsYexact.value(i - 1) + h * k3);
            leForRk.append(pointsYexact.value(i) - pointsYexact.value(i - 1) - h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));

        }
    }

    void findEulerGlobalError(int n){
        geForEuler.clear();
        for (int i = 0; i < n + 1; i++)
            geForEuler.append(abs(pointsYexact.value(i) - pointsYeuler.value(i)));
    }

    void findImpeulerGlobalError(int n){
        geForImpeuler.clear();
        for (int i = 0; i < n + 1; i++)
            geForImpeuler.append(abs(pointsYexact.value(i) - pointsYimpeuler.value(i)));
    }

    void findRkGlobalError(int n){
        geForRk.clear();
        for (int i = 0; i < n + 1; i++)
            geForRk.append(abs(pointsYexact.value(i) - pointsYrk.value(i)));
    }

    void findTotalApproximationGlobalErrors(int n0, int N1, double x0, double y0, double X){

        for (int i = n0; i < N1 + 1; i++){

            Solutions points = {x0, y0, X, i};
            points.exact();
            points.eulerMethod();
            points.impEulerMethod();
            points.rungeKuttaMethod();
            pointsX = points.pointsX;
            pointsYeuler = points.pointsYeuler;
            pointsYimpeuler = points.pointsYimpeuler;
            pointsYrk = points.pointsYrk;
            pointsYexact = points.pointsYexact;

            geForEuler.clear();
            findEulerGlobalError(i);
            double maximum = geForEuler.value(0);
            for (int j = 0; j < geForEuler.length(); j++)
                if (geForEuler.value(j) > maximum)
                    maximum = geForEuler.value(j);
            maxgeForEuler.append(maximum);

            geForImpeuler.clear();
            findImpeulerGlobalError(i);
            maximum = geForImpeuler.value(0);
            for (int j = 0; j < geForImpeuler.length(); j++)
                if (geForImpeuler.value(j) > maximum)
                    maximum = geForImpeuler.value(j);
            maxgeForImpeuler.append(maximum);

            geForRk.clear();
            findRkGlobalError(i);
            maximum = geForRk.value(0);
            for (int j = 0; j < geForRk.length(); j++)
                if (geForRk.value(j) > maximum)
                    maximum = geForRk.value(j);
            maxgeForRk.append(maximum);
        }
    }

    void findTotalApproximationLocalErrors(int n0, int N1, double x0, double y0, double X){

        for (int i = n0; i < N1 + 1; i++){

            Solutions points = {x0, y0, X, i};
            points.exact();
            points.eulerMethod();
            points.impEulerMethod();
            points.rungeKuttaMethod();
            pointsX = points.pointsX;
            pointsYeuler = points.pointsYeuler;
            pointsYimpeuler = points.pointsYimpeuler;
            pointsYrk = points.pointsYrk;
            pointsYexact = points.pointsYexact;

            leForEuler.clear();
            findEulerLocalError(i);
            double maximum = leForEuler.value(0);
            for (int j = 0; j < leForEuler.length(); j++)
                if (leForEuler.value(j) > maximum)
                    maximum = leForEuler.value(j);
            maxleForEuler.append(maximum);

            leForImpeuler.clear();
            findImpeulerLocalError(i);
            maximum = leForImpeuler.value(0);
            for (int j = 0; j < leForImpeuler.length(); j++)
                if (leForImpeuler.value(j) > maximum)
                    maximum = leForImpeuler.value(j);
            maxleForImpeuler.append(maximum);

            leForRk.clear();
            findRkLocalError(i);
            maximum = leForRk.value(0);
            for (int j = 0; j < leForRk.length(); j++)
                if (leForRk.value(j) > maximum)
                    maximum = leForRk.value(j);
            maxleForRk.append(maximum);
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
