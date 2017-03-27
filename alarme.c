#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <time.h>


void tempo(int pauseTime){
	//CETTE FONCTION FAIT UNE TEMPORISATION DE "pause secondes"
	time_t startTime,currentTime;
	time( &startTime );           		 // on recupere l'heure ORIGINE sous forme d'entier(nbr de secondes)

	while((time( &currentTime )-startTime<=pauseTime )){
		//ATTENTE
	        //fprintf(stderr,"\nDANS Delai de %d secondes",currentTime);

	}
        fprintf(stderr,"\nFin Delai de %d secondes \n",pauseTime);
}

void alarme(struct tm *newTime,int mode, char cmdSong[]){

	//time_t delai,nowTime,nowTimeTmp,atTime;
	time_t nowTime,nowTimeTmp,atTime;
	int delai;
	struct tm *newTimeTmp;

	if(mode==0){//IN mode
		delai=newTime->tm_hour*60*60+newTime->tm_min*60+newTime->tm_sec;
	}
	else if(mode==1){//AT mode
		time( &nowTime );         // on recupere l'heure ACTUELLE sous forme d'entier(nbr de secondes)
		newTimeTmp = localtime( &nowTime );	 // Convertion

		atTime=newTime->tm_hour*60*60+newTime->tm_min*60+newTime->tm_sec;//conversion
		nowTimeTmp=newTimeTmp -> tm_hour*60*60+newTimeTmp->tm_min*60+newTimeTmp->tm_sec;
		delai=atTime-nowTimeTmp;
	        //fprintf(stderr,"\natTime=  / ",atTime;

	}

	fprintf(stderr,"\nDelai de %d secondes",delai);
	//TEMPORISATION
	tempo(delai);

	//APRES LE DELAI,ON JOUE LE SON DE L'ALARME
	//system("cvlc audio/alarme.mp3");
	system(cmdSong);

}

int main(int argc,char **argv)
{
	struct tm newTime;
	char commande[200] = {0};

	if(argc==6){

		newTime.tm_hour=(unsigned int)atoi(argv[3]);
		newTime.tm_min=(unsigned int)atoi(argv[4]);
		newTime.tm_sec=(unsigned int)atoi(argv[5]);

		snprintf(commande, 200, "cvlc %s", argv[2]);

		if(strcmp(argv[1],"in")==0){
			alarme(&newTime,0,commande);
		}
		else if(strcmp(argv[1],"at")==0){
			alarme(&newTime,1, commande);
		}
	}

	else{
		printf("\nNombre de parametres incorrecte\n\tAide : alarm in/at heure min sec.\n");
	}
	return 0;
}
