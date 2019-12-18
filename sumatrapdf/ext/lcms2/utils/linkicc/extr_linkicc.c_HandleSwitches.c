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
 void* Copyright ; 
 void* Description ; 
 int EOF ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int /*<<< orphan*/  Help (void*) ; 
 double InkLimit ; 
 void* Intent ; 
 void* KeepLinearization ; 
 void* NumOfGridPoints ; 
 double ObserverAdaptationState ; 
 int PrecalcMode ; 
 void* TRUE ; 
 void* TagResult ; 
 int Verbose ; 
 double Version ; 
 double atof (void*) ; 
 void* atoi (void*) ; 
 void* cOutProf ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* lUse8bits ; 
 int /*<<< orphan*/  stderr ; 
 int xgetopt (int,char**,char*) ; 
 void* xoptarg ; 

__attribute__((used)) static
void HandleSwitches(int argc, char *argv[])
{
    int s;

    while ((s = xgetopt(argc,argv,"a:A:BbC:c:D:d:h:H:k:K:lLn:N:O:o:r:R:T:t:V:v:xX8y:Y:")) != EOF) {

    switch (s) {


        case 'a':
        case 'A':
            ObserverAdaptationState = atof(xoptarg);
            if (ObserverAdaptationState < 0 ||
                ObserverAdaptationState > 1.0)
                       FatalError("Adaptation state should be 0..1");
            break;

        case 'b':
        case 'B':
            BlackPointCompensation = TRUE;
           break;

        case 'c':
        case 'C':
            PrecalcMode = atoi(xoptarg);
            if (PrecalcMode < 0 || PrecalcMode > 2) {
                FatalError("Unknown precalc mode '%d'", PrecalcMode);
            }
           break;

       case 'd':
       case 'D':
           // Doing that is correct and safe: Description points to memory allocated in the command line.
           // same for Copyright and output devicelink.
           Description = xoptarg;
           break;

        case 'h':
        case 'H':
            Help(atoi(xoptarg));
            return;

        case 'k':
        case 'K':
            InkLimit = atof(xoptarg);
            if (InkLimit < 0.0 || InkLimit > 400.0) {
                FatalError("Ink limit must be 0%%..400%%");
            }
           break;


        case 'l':
        case 'L': KeepLinearization = TRUE;
           break;

       case 'n':
       case 'N':
           if (PrecalcMode != 1) {
               FatalError("Precalc mode already specified");
           }
           NumOfGridPoints = atoi(xoptarg);
           break;

        case 'o':
        case 'O':
            cOutProf = xoptarg;
           break;


       case 'r':
       case 'R':
          Version = atof(xoptarg);
          if (Version < 2.0 || Version > 4.3) {
              fprintf(stderr, "WARNING: lcms was not aware of this version, tag types may be wrong!\n");
          }
          break;

        case 't':
        case 'T':
            Intent = atoi(xoptarg);  // Will be validated latter on
            break;

        case 'V':
        case 'v':
            Verbose = atoi(xoptarg);
            if (Verbose < 0 || Verbose > 3) {
                FatalError("Unknown verbosity level '%d'", Verbose);
            }
            break;

        case '8':
            lUse8bits = TRUE;
            break;



        case 'y':
        case 'Y':
            Copyright = xoptarg;
            break;



       case 'x':
       case 'X': TagResult = TRUE;
           break;



       default:

           FatalError("Unknown option - run without args to see valid ones.\n");
        }
    }
}