#include "red.h"


dataset::dataset(string name,int xs,int ys, int filas){
    X=xs;
    Y=ys;
    Filas=filas;
    Datos.assign(filas,vector<double>(xs+ys,0));
    //Accdere archivo
    ifstream myfile(name.c_str());

    //Si el archivo existe
    if (myfile.is_open() ){
        string line;
        //Leer primera fila
        getline(myfile, line);

        //Leer las otras filas del archivo (Datos)
        for (int i = 0; i < filas; i++){
            for (int j = 0; j < xs+ys; j++){
                myfile >> Datos[i][j];
            }
        }
        //Cerrar archivo
        myfile.close();
    }
    //Si el archivo no existe
    else{
        cout << "Error archivo dado no existe\n";
        exit(-1);
    }

}

void dataset::Transformada(){

    varianza.assign(X,0);
    media.assign(X,0);


    for (int i = 0; i < Filas; i++){
        for (int j = 0; j < X; j++){
            if(j==0){
                media[j]=media[j]+Datos[i][j];
            }
            if(j==1){
                media[j]=media[j]+Datos[i][j];
            }
            if(j==2){
                media[j]=media[j]+Datos[i][j];
            }
            if(j==3){
                media[j]=media[j]+Datos[i][j];
            }
        }
    }
    for (int j = 0; j < X; j++){
        media[j]=media[j]/Filas;
    }

    for (int i = 0; i < Filas; i++){
        for (int j = 0; j < X; j++){
            if(j==0){
                varianza[j]=varianza[j]+pow((Datos[i][j] - media[j]), 2.0);
            }
            if(j==1){
                varianza[j]=varianza[j]+pow((Datos[i][j] - media[j]), 2.0);
            }
            if(j==2){
                varianza[j]=varianza[j]+pow((Datos[i][j] - media[j]), 2.0);
            }
            if(j==3){
                varianza[j]=varianza[j]+pow((Datos[i][j] - media[j]), 2.0);
            }
        }
    }
    for (int j = 0; j < X; j++){
        varianza[j]=varianza[j]/(Filas-1);
        varianza[j]=sqrt(varianza[j]);
    }

    for (int i = 0; i < Filas; i++){
        for (int j = 0; j < X; j++){
            /*if(j==0){
                Datos[i][j]=(Datos[i][j] - media[j])/varianza[j];
            }*/
            if(j==1){
                Datos[i][j]=(Datos[i][j] - media[j])/varianza[j];
            }
            if(j==2){
                Datos[i][j]=(Datos[i][j] - media[j])/varianza[j];
            }
            if(j==3){
                Datos[i][j]=(Datos[i][j] - media[j])/varianza[j];
            }
        }
    }
}


//////////////////////////////////////////////////

/////////////////////////Clase neuron/////////////////////////

neuron::neuron(int n_pesos){
    pesos.assign(n_pesos,0);
    for (int i = 0; i < n_pesos; i++){
        pesos[i]=drand48()* (1-(-1)) + (-1);
    }
}

//////////////////////////////////////////////////

/////////////////////////Clase layer/////////////////////////


layer::layer(int numero_neuronas,int numero_pesos){
    pesos_matriz.assign(numero_pesos,vector<double>(numero_neuronas,0));

    entradas.assign(numero_neuronas,0);
    salidas.assign(numero_pesos,0);

    for (int i = 0; i < numero_neuronas; i++){
        neuron N1(numero_pesos);
        for (int j= 0; j< numero_pesos; j++){
            pesos_matriz[j][i]=N1.pesos[j];

        }

        neuronas.push_back(N1);
    }

}

void layer::producto(){
    for (unsigned int i = 0; i < pesos_matriz.size() ; i++){
        salidas[i]=0;
        for (unsigned int j= 0; j< pesos_matriz[0].size(); j++){

            salidas[i]=salidas[i]+( pesos_matriz[i][j]*entradas[j]);
        }
    }
}

void layer::activacion(){
    for (unsigned int i = 0; i < entradas.size() ; i++){
        entradas[i]= 1/(1+exp(-entradas[i]));
    }
}



//////////////////////////////////////////////////

/////////////////////////Clase neuralnetwork/////////////////////////

double neuralnetwork::error (vector<double> dat){
    double error=0;

    for(unsigned int i=0; i < layers[layers.size()-1 ].entradas.size();i++ ){
        error=error+ ( pow( (layers[layers.size()-1 ].entradas[i] - dat[X+i]), 2) );
    }
    error=error/layers[layers.size()-1 ].entradas.size();
    return error;
}

neuralnetwork::neuralnetwork(int num_layers,int num_neurons,int xs, int ys){
    X=xs;
    Y=ys;

    layer entrada(xs+1,num_neurons);
    layers.push_back(entrada);

    for (int i = 0; i < num_layers-1 ; i++){
        layer capa(num_neurons,num_neurons);
        layers.push_back(capa);
    }
    layer cap(num_neurons,ys);
    layers.push_back(cap);

    layer fin(ys,1);
    layers.push_back(fin);
}

void neuralnetwork::forward_propagation( vector<double> Datos){
    for (int j = 0; j < X ; j++){
        layers[0].entradas[j]=Datos[j];
    }
    layers[0].entradas[X]=1;

    for (unsigned int i = 0; i < layers.size() ; i++){
        if(i==0){
            layers[i].producto();
        }
        else if(i>0){
            for (unsigned int k = 0; k < layers[i].entradas.size() ; k++){
                layers[i].entradas[k]=layers[i-1].salidas[k];
            }
            layers[i].activacion();
            layers[i].producto();

        }

    }
}

void neuralnetwork::random_pesos(vector < vector<double> > datos){

    double peso_actual=0;
    double error_actual=0;
    double nuevo_error=0;
    for (unsigned int i = 0; i < layers.size() ; i++){
        for (unsigned int j = 0; j < layers[i].pesos_matriz.size() ; j++){
            for (unsigned int k = 0; k < layers[i].pesos_matriz[j].size() ; k++){
                peso_actual=layers[i].pesos_matriz[j][k];

                error_actual=error_todo(datos);
                layers[i].pesos_matriz[j][k]=drand48()* (1-(-1)) + (-1);
                nuevo_error=error_todo(datos);
                if(nuevo_error>error_actual){
                    layers[i].pesos_matriz[j][k]=peso_actual;
                }
            }
        }
    }
}

double neuralnetwork::error_todo(vector < vector<double> > Datos){

    double error_T=0;
    for (unsigned int i = 0; i < Datos.size() ; i++){
        forward_propagation(Datos[i]);
        error_T=error_T+error(Datos[i]);

    }

    return error_T;
}

double neuralnetwork::todo(vector < vector<double> > Datos,int max_gen){
    int contador=0;
    double error_T=0;

    QString cc;
    QString ee;
    max_x=0;
    max_y=0;
    while(contador<=max_gen){
        error_T=error_todo(Datos);

        cc.sprintf("%d",contador);
        ee.sprintf("%lf",error_T);
        erroresepocas=erroresepocas+"Generacion: "+ cc+", error Total:"+ee+"\n";
        if(error_T > max_y){
            max_y=error_T;
        }
        errores.push_back(error_T);
        indices.push_back(contador);
        random_pesos(Datos);
        contador=contador+1;

    }
    max_x=max_gen;

    QString ii;
    QString jj;
    QString kk;
    QString ll;
    for (unsigned int i = 0; i < layers.size()-1 ; i++){
        for (unsigned int j = 0; j < layers[i].pesos_matriz.size() ; j++){
            for (unsigned int k = 0; k < layers[i].pesos_matriz[j].size() ; k++){
                ii.sprintf("%d",i);
                jj.sprintf("%d",j);
                kk.sprintf("%d",k);
                ll.sprintf("%lf",layers[i].pesos_matriz[j][k]);
                pesos=pesos+"Peso["+ii+"]["+jj+"]["+kk+"] ="+ll+"\n" ;

            }
        }
    }

    return error_T;
}
