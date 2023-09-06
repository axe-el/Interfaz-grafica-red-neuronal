#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "red.h"
#include <QFileDialog>
#include <QDir>

int global_capas=2;
int global_neuronas=8;
int global_generaciones=10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    global_capas=arg1;
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    global_neuronas=arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    global_generaciones=arg1;
}

void MainWindow::on_pushButton_clicked()
{
    QString strCount;
    double valor;

    dataset info( filename.toStdString() ,4,1,100);
    info.Transformada();

    neuralnetwork segunda(global_capas,global_neuronas,4,1);
    valor=segunda.todo(info.Datos,global_generaciones);

    strCount.sprintf("%lf",valor);
    ui->label_5->setText(strCount);
    ui->textBrowser->setText(segunda.pesos);
    ui->textBrowser_2->setText(segunda.erroresepocas);

    MainWindow::makePlot(segunda.indices,segunda.errores,segunda.max_x,segunda.max_y);


    QBrush greenBrush(Qt::blue);
    QBrush blueBrush(Qt::black);
    QBrush redBrush(Qt::red);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    QPen weightPen(Qt::black);
    weightPen.setWidth(2);
    int neuronRadius = 20;
    int layerSpace = 100;
    int neuronSpace = 40;
    scene->clear();

    for (unsigned int i = 0; i < segunda.layers.size(); i++) {
        for (unsigned int j = 0; j < segunda.layers[i].pesos_matriz.size(); j++) {
            for (unsigned int k = 0; k < segunda.layers[i].pesos_matriz[j].size() ; k++) {
                if(i<segunda.layers.size()-1)
                    scene->addLine(i*layerSpace+(.5*neuronRadius), k*neuronSpace+.5*neuronRadius, (i+1)*layerSpace+.5*neuronRadius, j*neuronSpace+.5*neuronRadius, weightPen);
                scene->addEllipse(0+(i)*layerSpace, 0+k*neuronSpace, neuronRadius, neuronRadius, outlinePen, greenBrush);

            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString file= QFileDialog::getOpenFileName(this,"Open",QDir::homePath());
    filename=file;
}

void MainWindow::makePlot(QVector<double> x, QVector<double> y, double max, double may){

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Epocas");
    ui->customPlot->yAxis->setLabel("Error_Total");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, max);
    ui->customPlot->yAxis->setRange(0, may);
    ui->customPlot->replot();

}
