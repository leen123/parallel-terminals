#include "pvm3.h"

/* Maximum number of children this program will spawn */
#define MAXNCHILD  100
/* Tag to use for the joing message */
#define JOINTAG    11
int times=0;
char str[2000];
int station;
int numPerson;
int numPersonFind;
int numPersonSent;
int numCars;
int numCarsEmpty;
int numSortCars;
int tempSortCars[MAXNCHILD];
int startTimeCars[MAXNCHILD];
int capacityCars[MAXNCHILD];
int timeCars[MAXNCHILD];
int availbleCars[MAXNCHILD];
int sortCars[MAXNCHILD];

//function
//************************//
//findStation 1:Damascus  2:Beirut
char* findStation(int station1){
		if(station1==1) return "Damascus";
		else return "Beirut";
	}
//sort cars 
int* sort(){
	int tempNumPerson= numPersonFind;
	int i;
	numSortCars=0;
	for ( i= 0; i < numCars; i++){
		if(availbleCars[i]>0){
			if(numPersonFind>0){
				availbleCars[i]=0;
				numSortCars++;
				numCarsEmpty--;
				startTimeCars[i]=times;
			}
			tempSortCars[i]=capacityCars[i];
			if(tempSortCars[i]>numPersonFind)
				tempSortCars[i]=numPersonFind;
			numPersonFind-=tempSortCars[i];
			numPersonSent+=tempSortCars[i];
		//	printf("a : %d\n", startTimeCars[i]);
		}else{
				tempSortCars[i]=sortCars[i];
		}
		 //printf("a : %d\n", tempSortCars[i]);
	}
	return tempSortCars;
}
//start program
void start(){
	int i;
	//station=1;
	//***************************//
	//********    1    **********//
	//***************************//
	if(station==1){
	numPerson=20;
	numPersonFind=numPerson;
    numPersonSent=0;
	numCars=3;
	numCarsEmpty=numCars;
	/////capacity Damascus//////
	capacityCars[0]=2;
	capacityCars[1]=3;
	capacityCars[2]=4;
	/////time//////
	 timeCars[0]=2;
	  timeCars[1]=3;
	   timeCars[2]=3;
	}
	
    //***************************//
	//********    2    **********//
	//***************************//
	else{
	numPerson=20;
	numPersonFind=numPerson;
    numPersonSent=0;
	numCars=3;
	numCarsEmpty=numCars;
	/////capacity Damascus//////
	capacityCars[0]=2;
	capacityCars[1]=3;
	capacityCars[2]=3;
	capacityCars[2]=7;
	/////time//////
	 timeCars[0]=2;
	  timeCars[1]=3;
	   timeCars[2]=3;
	   timeCars[2]=5;
	}
	
	//***************************//
	//********         **********//
	//***************************//
	/////availble/////
	   for (i = 0; i < numCars; i++){
		   startTimeCars[i]=0;
		   availbleCars[i]=1;
		   sortCars[i]=0;
	   }
	//////////
	   printf("numPerson : %d\n", numPerson);
	    printf("numCars : %d\n", numCars);
		printf("Cars : ");
	   for (i = 0; i < numCars; i++){
		   printf(" %d %d,", capacityCars[i],timeCars[i]);
	   }
	    printf("\n------------------------\n");
}
void sorten(){
	int i;
	 sort();
	   for (i = 0; i < numCars; i++){
		   sortCars[i]=tempSortCars[i];
		   //availbleCars[i]=0;
	   }
	   
	   	
	   	printf("numPersonFind: %d\n", numPersonFind);
		printf("numPersonSent: %d\n", numPersonSent);
		printf("numCarsEmpty : %d\n", numCarsEmpty);
		printf("numSortCars : %d\n", numSortCars);
		
		printf("Cars : ");
	   for (i = 0; i < numCars; i++){
		   printf(" %d ,", sortCars[i]);
	   }
	   printf("\n------------------------\n");
	   
	
	   		
}
int main(int argc, char* argv[])
{

	/* number of tasks to spawn, use 3 as the default */
	int ntask = 1;
	/* return code from pvm calls */
	int info;
	/* my task id */
	int mytid;
	/* my parents task id */
	int myparent;
	/* children task id array */
	int child[MAXNCHILD];
	int i, mydata, buf, len, tag, tid;
	int time;
	//*****************************//
	int pvm_capaCity,pvm_timeCar,pvm_station,pvm_index;
	  
	//*****************************//

	/* find out my task id number */
	mytid = pvm_mytid();
	//printf(" %d", mytid);
	/* check for err  or */
	if (mytid < 0) {
		/* print out the error */
		pvm_perror(argv[0]);
		/* exit the program */
		return -1;
	}
	/* find my parent's task id number */
	myparent = pvm_parent();
//	printf(" %d", myparent);
	/* exit if there is some error other than PvmNoParent */
	if ((myparent < 0) && (myparent != PvmNoParent)&& 
							(myparent != PvmParentNotSet)) 
	{
			pvm_perror(argv[0]);
			pvm_exit ();
			return -1;
	}
	/* if i don't have a parent then i am the parent */
	if (myparent == PvmNoParent || myparent == PvmParentNotSet) 
	{
		pvm_spawn("Demo", (char**)0, PvmTaskDefault, 
							(char*)0,2, child);
			for (i = 0; i < 2; i++){
				station=i+1;
				pvm_initsend(PvmDataDefault);
				pvm_pkint(&station,1,1);
				pvm_send(child[i], JOINTAG);
				}

			for (i = 0; i < 2; i++){
					buf = pvm_recv(child[i], JOINTAG);
				pvm_upkint(&station,1,1);
				pvm_upkstr(str);
				printf("%s\n",str);
				}
		
		pvm_exit();
		return 0;
	}
	else
	{	
		buf = pvm_recv(myparent, JOINTAG);
			pvm_upkint(&station,1,1);
			printf("***********************************\n** \tStation %s \t**\n***********************************\n",findStation(station));
strcpy(str, "***********************************\n** \tStation %s \t**\n***********************************\n",findStation(station));
		



								
	//*****************************//
	start();
	sorten();
			//			
	info = pvm_spawn("hello_other", (char**)0, PvmTaskDefault, 
							(char*)0,numSortCars, child);

		for (i = 0; i < numSortCars; i++){
			pvm_initsend(PvmDataDefault);
			pvm_pkint(&sortCars[i],1,1);
			pvm_pkint(&timeCars[i],1,1);
			pvm_pkint(&i,1,1);
			pvm_pkint(&station,1,1);
			pvm_send(child[i], JOINTAG);
		//	printf("car id %d is ------------------\n", i);
		}
		
	//	/* print out the task ids */
		for (i = 0; i < numSortCars; i++)
			if (child[i] < 0) /* print the error code in decimal*/
				printf(" %d", child[i]);
			else /* print the task id in hex */
				printf("t%x\t", child[i]);
		putchar('\n');
 
		/* make sure spawn succeeded */
		if (info == 0) { pvm_exit(); return -1; }

		/* only expect responses from those spawned correctly */
		ntask = info;
		//time
		 times = 0;
	//	int breake = 0;
		while(numPersonFind>0||numCarsEmpty<numCars){
			times++;
			printf("************%d************\n", times);
			for (i = 0; i < numCars; i++) {
				if(availbleCars[i]<1){
					if(times-startTimeCars[i]==timeCars[i]){
						if(station==1)
							printf("car id %d arrivel %d preson to %s\n", i,sortCars[i],findStation(2));
						else 
							printf("car id %d arrivel %d preson to %s\n", i,sortCars[i],findStation(1));
						sortCars[i]=0;
					}else if(times-startTimeCars[i]==2*timeCars[i]){
							availbleCars[i]=1;
							numCarsEmpty++;
							buf = pvm_recv(-1, JOINTAG);
							if (buf < 0) pvm_perror("calling recv");
							info = pvm_bufinfo(buf, &len, &tag, &tid);
							if (info < 0) pvm_perror("calling pvm_bufinfo");
						//	pvm_upkstr(buf);
							//pvm_upkint(index);
						//	 pvm_upkint(&index,1,1);
								pvm_upkint(&pvm_index,1,1);
						//	pvm_upkint(&pvm_station,1,1);
							printf("car id %d is back to %s\n", i,findStation(station));
						//	info = pvm_upkint(&mydata, 1, 1);
						//	if (info < 0) pvm_perror("calling pvm_upkint");
						//	if (mydata != tid) printf("This should not happen!\n");
						//	printf("Length %d, Tag %d, Tid t%x\n", len, tag, tid);

					}
				}
			}
			sorten();
			if(numSortCars>0)
			pvm_spawn("hello_other", (char**)0, PvmTaskDefault, 
							(char*)0,numSortCars, child);
			for (i = 0; i < numCars; i++){
				if(times==startTimeCars[i]){
				//	printf("Le %d",i);
					pvm_initsend(PvmDataDefault);
				pvm_pkint(&sortCars[i],1,1);
				pvm_pkint(&timeCars[i],1,1);
				pvm_pkint(&i,1,1);
				pvm_pkint(&station,1,1);
				pvm_send(child[i], JOINTAG);
				}
			
		}
		}
//******************





		pvm_initsend(PvmDataDefault);
			pvm_pkint(&station,1,1);
			pvm_pkstr(str);
		pvm_send(myparent, JOINTAG);
		pvm_exit();
		return 0;
	}
}

