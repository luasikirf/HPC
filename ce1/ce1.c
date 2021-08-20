#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int n = 10; int mu =10; int generaciones = 10; float alfa = 0.001; float epsilon = 0.001; int m = 2; int n2 = 21;

double f(double x[2*n]){
    //ya funciona correctamente
    int i =0;
    double termino1,termino2,sumCuadrados,sumCos;
    sumCuadrados = 0; sumCos = 0;
    for(i = 0; i < n; i++){
        sumCuadrados += (double)pow(x[i],2);
        sumCos +=(double)cos(2* acos(-1)*x[i]);
        }
 /*   printf("n= %i \n",n);
    printf("%i",1/n);
    printf("\n sumCuadrados:%.5f",sumCuadrados);  */
    termino1 =   -20 * exp( -0.2 * sqrt((double) 1/n * (double)sumCuadrados ) ) ;
    termino2 = -exp((double)1/n* sumCos) ;
    //printf("termino 1: %f termino 2: %f \n sumCuadrados:%.5f sumCos:%.5f \n",termino1,termino2,sumCuadrados,sumCos);
    return -(double) ( termino1+termino2+20+exp(1) );
}


void inicial(double soluciones[mu][n2]){
    int i; int j;
    //printf("%i",n2);
    // creamos los mu individuos en este ciclo
    for(j =0; j < mu; j++){
        //definimos el tamaño de cada individuo, es 2*n + 1 ya que son n variables de decicion, n factores de mutacion y su valor en f(x)
        double individuo[n2];
        //en este ciclo creamos las n variables que tiene cada individuo, en este caso son 2*n, ya que son n variables de decicion, y n factores de mutacion, el ultimo valor no es variable, por eso solo hacemos 2*n veces este ciclo.
        for (i=0;i < n2; i++){
            if (i < n2-1){
                          individuo[i]=(float)((rand()%1000)/1000.0f);
                          soluciones[j][i]=individuo[i];
            }
            else{
                individuo[i] =  f(individuo);//f(individuo);
                soluciones[j][i] = individuo[i];
                }
        }
        
/*        for (i=0;i < n2; i++){
            
            printf("%.4f,",individuo[i]);
            //printf("%.4f,",soluciones[j][i]);
        }*/
        
        
    }
    printf("padres creados con exito \n");
}

void copear(double a[n2], double b[n2]){
    for(int i  = 0; i < n2; i++){
        b[i] = a[i];
    }
}

double mutacion(double padres[mu][n2], double hijos[mu][n2], int t){
    int i;
    //copeamos el valor de los padres a las variables hijos, para no alterar los padres
    for(i=0; i < mu; i++ ){
        copear(padres[i],hijos[i]);
        // modificamos las variables de tamaño de paso, y de decicion
        for(int j=0; j < n+1; j++){
            if(j < n){
              //  printf("\n valor %i antes mutacion, %f ",j,hijos[i][j]);
                //primero modificamos el tamaño de paso, que son los ultimos n elementos
                hijos[i][j+n]  = hijos[i][j+n] * (1+((double)((rand()%1000)/1000.0f)*alfa ));
                //verificamos que el tamaño de paso no sea menor a epsilon
                    if(hijos[i][j+n] < epsilon){
                        hijos[i][j+n] = epsilon;
                        }
                //mutamos las variables de decicion
                hijos[i][j] = hijos[i][j] + (hijos[i][j+n] * (double)((rand()%1000)/1000.0f));
                //verificamos los valores no se salgan del espacio de busqueda (-30,30)
                    if(hijos[i][j] < -30 ){
                        hijos[i][j] = -30 * (double)((rand()%1000)/1000.0f) ;
                        }
                    if(hijos[i][j] > 30 ){
                        hijos[i][j] = 30 * (double)((rand()%1000)/1000.0f);
                        }
             //   printf("\n valor %i despues mutacion, %f ",j,hijos[i][j]);
                
            }
            else{
              //  printf("\n valor %i antes mutacion, %f ",j,hijos[i][j+n]);
                hijos[i][j+n] = f(hijos[i]);
              //  printf("\n valor %i despues mutacion, %f ",j,hijos[i][j+n]);
            }
            
        }
        
    }
    printf("hijos %i creados con exito \n",t);
    
}

void definirP(double poblacion[2*mu][n2],double padres[mu][n2], double hijos[mu][n2], int t){
    for(int i = 0; i < mu; i++){
        copear(padres[i],poblacion[i]);
        copear(hijos[i],poblacion[i+mu]);
    }
    printf("poblacion actualizada %i vez \n",t);
}

void ordenarP(double poblacion[2*mu][n2]){
   // print(poblacion);
            for (int k = 0; k < (2*mu)-1; k++)
            {
                double aux[n2];
               // print(poblacion);
               // printf("\n");
                for (int f = 0; f < (2*mu) - k-1; f++)
                {
                    
                        if (poblacion[f][n2-1] < poblacion[f + 1][n2-1]){
                        
                        copear(poblacion[f+1],aux);
                       /* printf("auxiliar:");
                        imprimir(aux);
                        printf("\n");
                        print(poblacion);
                        poblacion[f] = poblacion[f + 1]; */
                        copear(poblacion[f],poblacion[f+1]);
                      //  print(poblacion);
                        //poblacion[f + 1] = aux;
                        copear(aux,poblacion[f]);
                    //    print(poblacion);
                    }
                }
            } //print(poblacion);
}

void ordenarM(double poblacion[m][n2]){
            for (int k = 0; k < m-1; k++)
            {double aux[n2];
                for (int f = 0; f < m - k-1; f++)
                    {if (poblacion[f][n2-1] < poblacion[f + 1][n2-1]){
                        copear(poblacion[f+1],aux);
                        copear(poblacion[f],poblacion[f+1]);
                        copear(aux,poblacion[f]);
                    }
                }
            }
            //printf("llegamos a ordenar las mejores soluciones \n");
    }

void actualizarPadres(double padres[mu][n2],double poblacion[2*mu][n2]){
    for(int i =0; i < mu; i++){
        copear(poblacion[i],padres[i]);
    }
}

void impr(double arr[n2]){
    for(int i =0; i < n2; i++){
        printf("%f",arr[i]);
    }
}

void print(double matriz[mu][n2]){
    for(int i =0; i < mu; i++){
        printf("\n");
        for(int j = 0; j < n2; j++){
            printf("%f",matriz[i][j]);
        }
    }
    printf("\n");
}


void imprimir(double mejores[m][n2]){
    double mejor[n2], peor[n2],mediana[n2];
 /*   printf("mejores");
    print(mejores);
    printf("\n");*/
    ordenarM(mejores); //ordenamos para obtener el mejor de los mejores y el peor de los mejores individuos
   // printf("ordenamos las mejores");
    impr(mejores[0]);
    copear(mejores[0],mejor); //definimos el mejor individuo solucion
    //printf("copeamos exitosamente el mejor individuo");
    copear(mejores[(m-1)],peor);
    impr(mejor); 
    //printf("\n");
    //impr(peor);
}


int main(){
    srand((unsigned)time(NULL));
    // recibimos los valores necesarios para el algoritmo
  /*  printf("Cuantas variables de decicion desea que tengan los individuos? \n"); scanf("%i",&n); 
    printf("Inserte la cantidad de individuos que componen a la poblacion por favor. \n");  
    scanf("%i",&mu); 
    printf("Ingrese el numero maximo de generaciones por iteracion del algoritmo.\n");  
    scanf("%i",&generaciones); 
    printf("Ingrese el valor de alfa\n");
    scanf("%f",&alfa);
    printf("Ingrese el valor de epsilon \n");
    scanf("%f",&epsilon);
    printf("Cuantas veces quiere que se itere el algoritmo? \n");
    scanf("%i",&m);
    n2 = (2*n) + 1; */
    double mejores[m][n2];
    for(int i =0; i<m; i++){
        printf("iteracion %i \n",i);
        double padres[mu][n2];
        //obtenemos a los padres 
        inicial(padres);
        
        //iteramos los procesos de cada generacion
        for(int t =0; t < generaciones; t++){
            //declaramos una poblacion vacia, la cual contendra 2 veces la cantidad de individuos (mu)
            double poblacion[2*mu][n2];
            double hijos[mu][n2];
            //obtenemos a los hijos mutando a los padres
            mutacion(padres,hijos,t);
            //la poblacion se compone de padres e hijos de cada generacion
            definirP(poblacion,padres,hijos,t);
            ordenarP(poblacion); //ordenamos de mayor a menor la poblacion
            actualizarPadres(padres,poblacion);//los padres de la siguiente generacion son los mejores mu individuos de la poblacion
            
        }//fin iterar generaciones
       // impr(padres[0]);
        copear(padres[0],mejores[i]); //el mejor individuo de la generacion en este caso es el primero en la lista de los padres
      //  printf("\n");
       // impr(mejores[i]);
        

    }//fin iterar m veces algoritmo
   // print(mejores);
    imprimir(mejores);
    
    
    
}//fin main


