#ifndef RED_H
#define RED_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

#include <bits/stdc++.h>
#include <time.h>


using namespace std;


class dataset {
    public:
        int X;
        int Y;
        int Filas;
        vector < vector<double> > Datos;
        vector<double> varianza;
        vector<double> media;

        dataset(string name, int xs,int ys, int filas);
        void Transformada();
        ~dataset(){}
};

class neuron{
    public:
        vector<double> pesos;
        neuron(int n_pesos);
        ~neuron(){}

    friend class layer;
};

class layer{
    public:
        vector<neuron> neuronas;
        vector < vector<double> > pesos_matriz;

        vector<double> entradas;
        vector<double> salidas;

        layer(int numero_neuronas,int numero_pesos);




        ~layer(){}
        void activacion();
        void producto();

    friend class neuralnetwork;
};

struct neuralnetwork{
    public:
        int X;
        int Y;
        QVector<double> errores;
        QVector<double> indices;
        vector<layer> layers;

        QString pesos;
        QString erroresepocas;
        double max_x;
        double max_y;


        neuralnetwork(int num_layers,int num_neurons,int xs, int ys);

        ~neuralnetwork(){}

        void forward_propagation(vector<double> Datos);
        double error (vector<double> dat);
        double error_todo(vector < vector<double> > Datos);
        void random_pesos(vector < vector<double> > datos);
        double todo(vector < vector<double> > Datos,int max_gen);

} ;

#endif // RED_H
