// test.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h> 
#include <iostream>
#include <conio.h>
#define wait 200
int count=0;
char key=NULL;
int ** matrix;
int i,j,zeile=5,spalte=5;
int xpos=0, ypos=0;
void printfeld(int** feld);
DWORD WINAPI  ThreadFunc(void* data);


int _tmain(int argc, _TCHAR* argv[])
{

	/* Speicher reservieren für die int-Zeiger (=zeile) */
   matrix =(int**)malloc(zeile * sizeof(int *));
   if(NULL == matrix) {
	  printf("Kein virtueller RAM mehr vorhanden ... !");
	  return EXIT_FAILURE;
   }
   /* jetzt noch Speicher reservieren für die einzelnen Spalten
	* der i-ten Zeile */
   for(i = 0; i < zeile; i++) {
	  matrix[i] = (int*)malloc(spalte * sizeof(int));
		 if(NULL == matrix[i]) {
			printf("Kein Speicher mehr fuer Zeile %d\n",i);
			return EXIT_FAILURE;
		 }
   }
   /* mit beliebigen Werten initialisieren */
   for (i = 0; i < zeile; i++)
	  for (j = 0; j < spalte; j++)
		 matrix[i][j] = 0;      /* matrix[zeile][spalte] */

   char key=NULL;
   matrix[ypos][xpos]=1;
   matrix[4][4]=2;
   printfeld(matrix);



   HANDLE thread1=CreateThread(NULL,0,ThreadFunc,NULL,0,NULL);


   do	{
		key=255;
		if(kbhit()) // Nur wenn auch eine Taste gedrückt ist
		{
		key = getch(); // Muss auf keine Eingabe warten, Taste ist bereits gedrückt
		}
		//printf("%d\r",key);
		switch (key)
		{
			case 0x0A:
			case 0x0D:
			// ignore CR/LF
			break;
			case 77:
				if(xpos<4&&matrix[ypos][xpos+1]==0)	{
					matrix[ypos][xpos]=0;
					matrix[ypos][++xpos]=1;
					count++;
				}
				printfeld(matrix);
				break;
			case 72:
				if(ypos>0&&matrix[ypos-1][xpos]==0)	
				{
					matrix[ypos][xpos]=0;
					matrix[--ypos][xpos]=1;
					count++;
				}
				printfeld(matrix);
				break;
			case 75:
				if(xpos>0&&matrix[ypos][xpos-1]==0)	{
					matrix[ypos][xpos]=0;
					matrix[ypos][--xpos]=1;
					count++;
				}
				printfeld(matrix);
				break;
			case 80:
				if(ypos<4&&matrix[ypos+1][xpos]==0)	{
					matrix[ypos][xpos]=0;
					matrix[++ypos][xpos]=1;
					count++;
				}
				printfeld(matrix);
				break;
			default:
			printf("");
		}
		
		} while (key!='q' && key!='Q');



	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED); 
	printf("test\ttest\atest");

	for(int i=0;i<10;i++){
		printf("|\r");
		Sleep(wait);
		printf("\\\r");
		Sleep(wait);
		printf("-\r");
		Sleep(wait);
		printf("/\r");
		Sleep(wait);
	}*/
	return 0;
}



void printfeld(int** feld)
{
	system("cls");

	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			printf("+---");
		}
		printf("+\n|");
		for(int j=0;j<5;j++)
		{
			if(feld[i][j]==1)
			{
			printf(" Y |");
			}
			if(feld[i][j]==2)
			{
			printf(" # |");
			}
			if(feld[i][j]==0)
			{
			printf("   |");
			}
		}
		printf("\n|");
		for(int j=0;j<5;j++)
		{
			if(feld[i][j]==1)
			{
			printf(" I |");
			}
			if(feld[i][j]==2)
			{
			printf(" # |");
			}
			if(feld[i][j]==0)
			{
			printf("   |");
			}
		}
		printf("\n");	
	}
	for(int j=0;j<5;j++)
		{
			printf("+---");
		}
	printf("+\n");
	printf(" q/Q: Beenden\t PFEILTASTEN: Bewegen\tZuege: %d\tProzessor: %d\r",count,GetCurrentProcessorNumber());
}

DWORD WINAPI  ThreadFunc(void* data){
	for(;;){
		printf("|\r");
		Sleep(wait);
		printf("\\\r");
		Sleep(wait);
		printf("-\r");
		Sleep(wait);
		printf("/\r");
		Sleep(wait);
	}
	printf("\nThread beendet!!!\n");
	return 0;
}


