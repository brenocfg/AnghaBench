#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 void* BlackPointCompensation ; 
 int EOF ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int Intent ; 
 void* NumOfGridPoints ; 
 int PrecalcMode ; 
 void* TRUE ; 
 void* Undecorated ; 
 void* atoi (void*) ; 
 void* cInProf ; 
 void* cOutProf ; 
 int xgetopt (int,char**,char*) ; 
 void* xoptarg ; 

__attribute__((used)) static
void HandleSwitches(int argc, char *argv[])
{
       int s;

       while ((s = xgetopt(argc,argv,"uUbBI:i:O:o:T:t:c:C:n:N:")) != EOF) {

       switch (s){


       case 'i':
       case 'I':
            cInProf = xoptarg;
            break;

       case 'o':
       case 'O':
           cOutProf = xoptarg;
            break;

       case 'b':
       case 'B': BlackPointCompensation =TRUE;
            break;


       case 't':
       case 'T':
            Intent = atoi(xoptarg);
            if (Intent > 3) Intent = 3;
            if (Intent < 0) Intent = 0;
            break;

       case 'U':
       case 'u':
            Undecorated = TRUE;
            break;

       case 'c':
       case 'C':
            PrecalcMode = atoi(xoptarg);
            if (PrecalcMode < 0 || PrecalcMode > 2)
                    FatalError("ERROR: Unknown precalc mode '%d'", PrecalcMode);
            break;


       case 'n':
       case 'N':
                if (PrecalcMode != 1)
                    FatalError("Precalc mode already specified");
                NumOfGridPoints = atoi(xoptarg);
                break;


  default:

       FatalError("Unknown option - run without args to see valid ones.\n");
    }
    }
}