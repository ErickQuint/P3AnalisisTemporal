#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include "hilo.c"

int main (int argc, char* argv[])
{
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medicion de tiempos
	int n; 	//n determina el tamanio del algorito dado por argumento al ejecutar
	int i; //Variables para loops
	int encontrado = -1;
	int NumThreads = 2 ;
	
	int cantidadABuscar = 20;
	int numerosABuscar[] = 
	{0,  10393545 , 1295390003 , 1360839354 , 14700764 , 1493283650 , 152503 , 1843349527 , 187645041 , 
	 1980098116 , 2109248666 , 2147445644 , 2147470852 , 214826 , 3128036 , 322486 , 450057883 , 5000 , 61396 , 6337399 
	};
		
	//******************************************************************	
	//Recepcion y decodificacion de argumentos
	//******************************************************************	

	//Si no se introducen exactamente 2 argumentos (Cadena de ejecucion y cadena=n)
	if (argc!=2) 
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	//Tomar el segundo argumento como tamanio del algoritmo
	else
	{
		n=atoi(argv[1]);
	}
	
	//******************************************************************
	//Reservar memoria del arreglo
	int *A = malloc(sizeof(int)*n);
	
	//leer numeros
	for(i=0;i<n;i++)
		scanf("%d",&A[i]);
		
	//******************************************************************	
	//Algoritmo Busqueda exponencial
	
	//******************************************************************
	for(i = 0; i < cantidadABuscar; i++){
		int x = numerosABuscar[i];
		
		uswtime(&utime0, &stime0, &wtime0);
		BusquedaExponencialHilos(A,x,0,n, &encontrado);
		uswtime(&utime1, &stime1, &wtime1);
		
		if(encontrado == 0)
			printf("%d SI\n", x);
		else
			printf("%d NO\n", x);	
		
			
		printf("\n");
		printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
		printf("user (Tiempo de procesamiento en CPU's) %.10f s\n",  utime1 - utime0);
		printf("%d threads (Tiempo de procesamiento aproximado por cada thread en CPU) %.10f s\n", NumThreads,(utime1 - utime0)/NumThreads);	
		printf("sys (Tiempo en acciónes de E/S)  %.3f s\n",  stime1 - stime0);
		printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
		printf("\n");
		
		encontrado = -1;	
	}
}
