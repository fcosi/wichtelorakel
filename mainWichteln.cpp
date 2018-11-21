
#include <stdio.h>  
#include <stdlib.h>      
#include <string>
#include <time.h>   

#define ELEMENT(s,b,teilnehmerZahl) ((s)+teilnehmerZahl*(b))
#define MAXIMALE_NAMENSLAENGE 123
using namespace std;

void initialisiereWichtelMatrix(int *wichtel_matrix,int teilnehmerZahl,int minimKreis)
{
	
	int *ist_im_kreis=(int *)malloc(sizeof(int)*teilnehmerZahl); 
	int *hat_schon_wichtel=(int *)malloc(sizeof(int)*teilnehmerZahl); 
	int *wichtelt_schon=(int *)malloc(sizeof(int)*teilnehmerZahl); 


	for(int i=0;i<teilnehmerZahl*teilnehmerZahl;i++) wichtel_matrix[i]=0;

	srand (time(NULL));

	int wichtel;
	int bewichtelter;
	int anzahl_gesetzter_wichtel=0;

	for(int i=0;i<teilnehmerZahl;i++)
	{
		hat_schon_wichtel[i]=0;
		wichtelt_schon[i]=0;
	}

	while(anzahl_gesetzter_wichtel<teilnehmerZahl)
	{
		//neuer Kreis:
		for(int i=0;i<teilnehmerZahl;i++) ist_im_kreis[i]=0;
		int kreislaenge=1;

		//finde ersten wichtel im Kreis
		while(1)
		{
			wichtel=(rand() % teilnehmerZahl);
			if(wichtelt_schon[wichtel]==1) continue;
			else
			{
				wichtelt_schon[wichtel]=1;
				ist_im_kreis[wichtel]=1;
				anzahl_gesetzter_wichtel++;
			}
			//printf("der erste Wichtel eines neuer Kreises wurde gesetzt: %d \n",wichtel);
			//printf("Anzahl gesetzter Wichtel: %d \n",anzahl_gesetzter_wichtel);
			break;
		}

		//finde Bewichtelten und setze ihn als neuen Wichtel, falls er noch keiner ist
		while(1)
		{
			//finde Bewichtelbaren
			while(1)
			{
				bewichtelter=(rand() % teilnehmerZahl);
				if(hat_schon_wichtel[bewichtelter]) continue;//{printf("fall a) \n");getchar(); continue;}
				if(kreislaenge<minimKreis && ist_im_kreis[bewichtelter]) continue;//{printf("fall b) \n");getchar(); continue;}
				if(teilnehmerZahl-(anzahl_gesetzter_wichtel)<minimKreis && teilnehmerZahl-(anzahl_gesetzter_wichtel)!=0 && ist_im_kreis[bewichtelter]) continue;//{printf("fall c) \n");getchar(); continue;}
				//printf("%d wurde als Bewichtelbarer gefunden \n", bewichtelter);
				break;
			}

			//setze gefundenen auf bewichtelt
			wichtel_matrix[ELEMENT(bewichtelter,wichtel,teilnehmerZahl)]=1;
			hat_schon_wichtel[bewichtelter]=1;
			ist_im_kreis[bewichtelter]=1;
			//printf("%d wird von %d bewichtelt \n", bewichtelter, wichtel);
			
				
			//Setze gefundenen auf Wichtel fall er noch keiner war
			//andernfalls beginne einen neuen Kreis
			if(wichtelt_schon[bewichtelter]) {/*printf("Ein Kreis mit Länge %d wurde erstellt\n, ",kreislaenge);*/break;}
			else 
			{
				wichtel=bewichtelter;
				wichtelt_schon[bewichtelter]=1;
				kreislaenge++;
				anzahl_gesetzter_wichtel++;
				//printf("%d wird zum Wichtel \n", wichtel);
				//printf("Anzahl gesetzter Wichtel: %d \n",anzahl_gesetzter_wichtel);
			}
		}

	}

	free(ist_im_kreis);
	free(hat_schon_wichtel);
	free(wichtelt_schon);

}

int main()
{

	printf("\nHo ho ho! Welcome to the Wichtel-Oracle!\n\n");
	printf("This tool creates several .txt files in its directory, of which \neach contains the mission for a certain secret Santa. \nPress Enter to start...\n");
	while(getchar()!='\n');

	//Anzahl an Teilnehmern abfragen
	printf("\n");
	printf("Please enter the number of participants:\n");
	int teilnehmerZahl;
	while(1)
	{
		scanf ("%d",&teilnehmerZahl);
		if(0<teilnehmerZahl&&teilnehmerZahl<2147483647)break;
		else printf("...invalid number!\n\n");
		while(getchar()!='\n');
		printf("Please enter the number of participants:\n");
	}
	

	//Minimale Kreislänge abfragen
	printf("\n");
	printf("Please enter the minimal circle size:\n(The number has to be between 1 and %d. At 1 you can be your own secret Santa)\n",teilnehmerZahl);
	int minimKreis;
	while(1)
	{
		scanf ("%d",&minimKreis);
		if(0<minimKreis&&minimKreis<=teilnehmerZahl)break;
		else printf("...invalid number!\n\n");
		while(getchar()!='\n');
		printf("Please enter the minimal circle size:\n(The number has to be between 1 and %d. At 1 you can be your own secret Santa)\n",teilnehmerZahl);
	}
	

	//Liste der Teilnehmer abfragen:
	printf("\n");
	string *laArray=(string *)malloc(sizeof(string)*teilnehmerZahl); 
	printf("Please enter participants' names:\n");
	for(int i=0;i<teilnehmerZahl;i++)
	{
		scanf ("%s",laArray+i);
	}
	while(getchar()!='\n');


	//Overview
	printf("\n");
	printf("------------------------------------------\n");
	printf("--------------- Overview -----------------\n");
	printf("------------------------------------------\n");
	printf("List of participants:\n");
	for(int s=0;s<teilnehmerZahl;s++)
	{
		printf ("%s\n",laArray+s);
	}
	printf("Minimal circle size:\t %d\n",minimKreis);
	printf("\n");
	printf("Press Enter to let the magic happen...\n");
	while(getchar()!='\n');


	//Wichtel-Matrix erzeugen
	int *wichtel_matrix=(int *)malloc(sizeof(int)*teilnehmerZahl*teilnehmerZahl); 
	initialisiereWichtelMatrix(wichtel_matrix,teilnehmerZahl,minimKreis);

	//Files mit Wichtel-Aufträgen erzeugen
	for(int s=0;s<teilnehmerZahl;s++)
	{
		for(int b=0;b<teilnehmerZahl;b++)
		{
			if(wichtel_matrix[ELEMENT(s,b,teilnehmerZahl)]==1)
			{
				FILE *file; 
				char file_name[100+MAXIMALE_NAMENSLAENGE];
				sprintf (file_name, "Wichtel-Mission for %s.txt",laArray+s);
				file = fopen(file_name,"w"); 
				fprintf(file, "Sei gegrüßt, %s! \n\ndu wurdest vom großen Wichtel-Orakel in seiner unendlichen Weisheit erkoren, ein Geschenk für %s zu beschaffen! \n\nViel Spaß beim Wichteln\nder Wichtel-Orakel-Zauberer\n\n",laArray+s,laArray+b);
				fprintf(file, "----------------------------------------\n\n");
				fprintf(file, "Greetings, %s!\n\nyou were chosen by the great Wichtel-Oracle in its infinite wisdom to provide a present for %s! \n\nhave fun playing secret Santa\nthe Wichtel-Oracle-Wizard",laArray+s,laArray+b);
				fclose(file); 
			}
		}
	}


	//Aufräumen
	free(wichtel_matrix);
	free(laArray);

    return 0;
}
