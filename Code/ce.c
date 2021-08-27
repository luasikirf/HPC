#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include <unistd.h>

int n = 2; int mu =10; int generaciones = 10; float alfa = 0.001; float epsilon = 0.001; int m = 1; int n2 = 5; int t = 3;

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
    //printf("padres creados con exito \n");
}
 
void aplanar(double matriz[][n2],double vector_vacio[], int renglones){
    
    for(int i =0; i<renglones;i++){
        for(int j=0; j < n2; j++){
            vector_vacio[(i*n2)+j] = matriz[i][j];
        }
    }
}

void desAplanar(double vector[], double matriz[][n2], int renglones){
    for(int i =0; i < renglones; i++){
        for(int j=0; j < n2; j++){
             matriz[i][j] = vector[(i*n2)+j];
        }
    }
}


void copear(double a[n2], double b[n2]){
    for(int i  = 0; i < n2; i++){
        b[i] = a[i];
    }
}

double mutacion(double padres[][n2], double hijos[][n2], int renglones){
    int i;
    //copeamos el valor de los padres a las variables hijos, para no alterar los padres
    for(i=0; i < renglones; i++ ){
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
    
}

void definirP(double poblacion[][n2],double padres[][n2], double hijos[][n2], int renglones){
    for(int i = 0; i < renglones; i++){
        copear(padres[i],poblacion[i]);
        copear(hijos[i],poblacion[i+renglones]);
    }
    //printf("poblacion actualizada %i vez \n",t);
}

void ordenarP(double poblacion[][n2], int renglones){
   // print(poblacion);
            for (int k = 0; k < (2*renglones)-1; k++)
            {
                double aux[n2];
               // print(poblacion);
               // printf("\n");
                for (int f = 0; f < (2*renglones) - k-1; f++)
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

void actualizarPadres(double padres[][n2],double poblacion[][n2], int renglones){
    for(int i =0; i < renglones; i++){
        copear(poblacion[i],padres[i]);
    }
}

void impr(double arr[], int elementos){
    for(int i =0; i < elementos; i++){
        printf("%f,",arr[i]);
    }
}

void print(double matriz[mu][n2], int individuos){
    for(int i =0; i < individuos; i++){
        printf("\n");
        for(int j = 0; j < n2; j++){
            printf("%f,",matriz[i][j]);
        }
    }
    printf("\n");
}

float std(double fs[m], float media){
    float c = 0;
    for(int i =0; i < m; i++){
        c = c + pow((fs[i]-media),2);
    }
    c = sqrt(c/m);
    return(c);
}

void imprimir(double mejores[][n2]){
    double mejor[n2], peor[n2],mediana[n2],fs[m];
    float media = 0.0; float desviacion = 0.0;
    for(int i =0; i < m; i++){
        fs[i] = fabs(mejores[i][n2-1]);
        media = media+ mejores[i][n2-1];
    }
    media = fabs(media / m);
    desviacion = std(fs,media);
 /*   printf("mejores");
    print(mejores);
    printf("\n");*/
 
    ordenarM(mejores); //ordenamos para obtener el mejor de los mejores y el peor de los mejores individuos
    copear(mejores[0],mejor);
    printf("Despues de %i iteraciones del algoritmo, estos son los resultados:\n",m);
    printf("\n******   La mejor solucion encontrada es: ******\n");
    impr(mejores[0],n2);
    printf("\nCon un valor en la funcion objetivo de: %f \n",fabs(mejor[n2-1]));

    if (fmod(m,2) ==0){
        printf("\n****** Medianas encontradas ******\n");
        printf("Como hay un numero par de soluciones, la mediana corresponde a una solucion que se encuentre entre las siguientes\n");
        printf("  La primer mediana es:");
        impr(mejores[m/2],n2);
        printf("\n Con un valor en la funcion objetivo de: %f\n",fabs(mejores[m/2][n2-1]));
        printf("  La segunda mediana es:");
        impr(mejores[(m/2)-1],n2);
        printf("\n Con un valor en la funcion objetivo de: %f\n",fabs(mejores[(m/2)-1][n2-1]));
    }
    else{
        printf("\n****** La mediana que se encontro es ******\n");
        impr(mejores[(m-1)/2],n2);
        printf("\nCon un valor en la funcion objetivo de: %f\n",fabs(mejores[(m-1)/2][n2-1]));
    }
    printf("\n******   La peor solucion encontrada es: ******\n");
    impr(mejores[m-1],n2);
    printf("\nCon un valor en la funcion objetivo de: %f \n",fabs(mejores[m-1][n2-1]));
    

    printf("\nla media del valor en F(x) que toman los resultados es: %f \n",media);
    printf("\nla desviacion estandar de los valores en F(x) es: %f\n",desviacion);
    
}


int main(int argc, char **argv){
    // recibimos los valores necesarios para el algoritmo
 /*   printf("Cuantas variables de decicion desea que tengan los individuos? \n"); scanf("%i",&n); 
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
    n2 = (2*n) + 1; 
    */
    
    MPI_Init (&argc,&argv); //iniciamos MPI
    srand(time(NULL) + getpid()); //ponemos semillas diferentes para el random de cada proceso
    //srand((unsigned)time(NULL));
    
    int numproc,miproc;
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &miproc);
    
    int mu_proc = mu/numproc;
    double mejores[m][n2];
    for(int i =0; i< m; i++){
        double iniciales[mu_proc][n2]; //obtenemos a los iniciales
         /*   if(miproc ==0){ printf("arreglo de padres creado\n"); } */
        int ii; int j; // creamos los mu/proc individuos en este ciclo
        for(j =0; j < mu_proc; j++){
        //definimos el tamaño de cada individuo, es 2*n + 1 ya que son n variables de decicion, n factores de mutacion y su valor en f(x)
            double individuo[n2];
        //en este ciclo creamos las n variables que tiene cada individuo, en este caso son 2*n, ya que son n variables de decicion, y n factores de mutacion, el ultimo valor no es variable, por eso solo hacemos 2*n veces este ciclo.
            for (ii=0;ii < n2; ii++){
                if (ii < n2-1){
                    individuo[ii]=(float)((rand()%1000)/1000.0f);
                    iniciales[j][ii]=individuo[ii];
                            }
            else{
                individuo[ii] =  f(individuo);//f(individuo);
                iniciales[j][ii] = individuo[ii];
                }
            }
        
        }
        //MPI_Barrier( MPI_COMM_WORLD ) ;    
        MPI_Barrier( MPI_COMM_WORLD ) ;
        //recibimos los padres de cada proceso excepto el maestro, y juntamos todos los resultados, incluyendo los del maestro
        if(miproc ==0){
            //printf("llegamos a donde deberiamos recibir datos\n");
            double padres[mu_proc*numproc][n2];
            double recividos[mu_proc*numproc*n2];
            //agregamos los padres iniciales del proceso 0 a la lista general que luego se hara matriz general
            for(int i =0; i<mu_proc; i++){
                for(int j =0; j < n2; j++){
                    recividos[(i*n2)+j] = iniciales[i][j];
                }
            }
           // print(padres,mu_proc);
            //impr(recividos,mu_proc*n2);
            //recibimos los padres iniciales de los otros procesos, y los unimos a la lista general
            for(int i=1; i<numproc; i++){
                double recivido[mu_proc*n2];
                MPI_Status estado;
                MPI_Recv(&recivido, mu_proc*n2, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
                for(int j=0; j<mu_proc*n2; j++){
                    recividos[(i*mu_proc*n2)+j] = recivido[j];
                }
            }
            desAplanar(recividos,padres,mu_proc*numproc);
            //printf("lo recibido es\n");
            //impr(recividos,mu_proc*numproc*n2);
            //printf("la poblacion total es: \n");
            //print(padres,mu_proc*numproc);
            
            for(int t =0; t < generaciones; t++){
                //declaramos una poblacion vacia, la cual contendra 2 veces la cantidad de individuos (mu)
                double poblacion[2*mu_proc*numproc][n2];
                double hijos[mu_proc*numproc][n2];
                mutacion(padres,hijos,mu_proc*numproc); //obtenemos a los hijos mutando a los padres
                //la poblacion se compone de padres e hijos de cada generacion
                definirP(poblacion,padres,hijos,mu_proc*numproc);
                ordenarP(poblacion,mu_proc*numproc); //ordenamos de mayor a menor la poblacion
                actualizarPadres(padres,poblacion,mu_proc*numproc);//los padres de la siguiente generacion son los mejores mu individuos de la poblacion
            }//fin iterar generaciones
            copear(padres[0],mejores[i]); //el mejor individuo de la generacion en este caso es el primero en la lista de los padres
            
            if(i == m-1){imprimir(mejores);}
        }
        else{
            double enviar[mu_proc*n2];
            aplanar(iniciales,enviar,mu_proc);
           // printf("soy el proceso %i y voy a enviar: \n prueba %i\n",miproc,10/miproc);
            //print(padres,mu_proc);
           // impr(enviar,mu_proc*n2);
            //printf("\n");
            MPI_Send(&enviar, mu_proc*n2, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD );
        }
         /*   //iteramos los procesos de cada generacion
            for(int t =0; t < generaciones; t++){
                //declaramos una poblacion vacia, la cual contendra 2 veces la cantidad de individuos (mu)
                double poblacion[2*mu][n2];
                double hijos[mu][n2];
                mutacion(padres,hijos,t); //obtenemos a los hijos mutando a los padres
                //la poblacion se compone de padres e hijos de cada generacion
                definirP(poblacion,padres,hijos,t);
                ordenarP(poblacion); //ordenamos de mayor a menor la poblacion
                actualizarPadres(padres,poblacion);//los padres de la siguiente generacion son los mejores mu individuos de la poblacion
                
            }//fin iterar generaciones
            
            
            copear(padres[0],mejores[i]); //el mejor individuo de la generacion en este caso es el primero en la lista de los padres
            */

        
    }//fin iterar m veces algoritmo
    
        //imprimir(mejores);
    MPI_Finalize();
    
   /* double ppp[2][5];
    double vetorp[10];
    
    aplanar(ppp,vetorp,2);
    
    for(int i =0; i <10; i++){
        vetorp[i]=1;
    }
    desAplanar(vetorp,ppp,2); */

}//fin main



