
#include "pvm3.h"

/* Maximum number of children this program will spawn */
#define MAXNCHILD  100
/* Tag to use for the joing message */
#define JOINTAG    11
int times=0;

char buf[100];
int station;
int numPerson;

int main(int argc, char* argv[])
{
	int timeCars[MAXNCHILD];
	int availbleCars[MAXNCHILD];
	int sortCars[MAXNCHILD];
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
		printf("can't start hello_other\n");
		pvm_exit();
		return 0;
	}
	else
	{		
	buf = pvm_recv(myparent, JOINTAG);
		pvm_upkint(&pvm_capaCity,1,1);
			pvm_upkint(&pvm_timeCar,1,1);
			pvm_upkint(&pvm_index,1,1);
			pvm_upkint(&pvm_station,1,1);
			printf("Length %d, Tag %d, Tid t%x\n", sortCars, pvm_timeCar, pvm_index);
			for (i = 0; i < 2*timeCars[pvm_index]; i++) ;
		pvm_initsend(PvmDataDefault);
		pvm_pkint(&pvm_index,1,1);
			pvm_pkint(&pvm_station,1,1);
		pvm_pkint(&mytid,1,1);
			
		pvm_send(myparent, JOINTAG);

		pvm_exit();
		return 0;
	}
}



/*
#include "pvm3.h"

main()
{
	int ptid;
	char buf[100];
	char buf1[100];

	ptid = pvm_parent();

	strcpy(buf, "hello, world from ");
	gethostname(buf + strlen(buf), 64);

	strcpy(buf1, "hello, world from1 ");
	gethostname(buf1 + strlen(buf1), 64);

	pvm_initsend(PvmDataDefault);
	pvm_pkstr(buf);
	pvm_pkstr(buf1);
	pvm_send(ptid, 1);

	pvm_exit();
	exit(0);
}*/
/*
#include <stdio.h>
#include "pvm3.h"

int main()
{
	int *A, *B;
	int i, s, m;
	int mytid, master;
	int info, bufid, tag;

	//mytid = pvm_mytid();
	master = pvm_parent();
	
	bufid = pvm_recv(master, -1);
	info = pvm_bufinfo(bufid, 0, &tag, 0);

	pvm_upkint(&m, 1, 1);
	
	A = (int*) malloc(m * sizeof(int));
	B = (int*) malloc(m * sizeof(int));
	
	pvm_upkint(A, m, 1);
	pvm_upkint(B, m, 1);

	s = 0;
	for (i=0; i<m; i++)
		s += A[i] * B[i];
	
	pvm_initsend(PvmDataDefault);
	pvm_pkint(&s, 1, 1);
	pvm_send(master, tag);

	pvm_exit();
	return 0;
}
*/