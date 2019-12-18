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
 void* BlackWhiteCompensation ; 
 int EOF ; 
 void* EmbedProfile ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 void* GamutCheck ; 
 int /*<<< orphan*/  Help (int) ; 
 void* IgnoreEmbedded ; 
 double InkLimit ; 
 void* Intent ; 
 double ObserverAdaptationState ; 
 int PrecalcMode ; 
 void* ProofingIntent ; 
 void* SaveEmbedded ; 
 void* StoreAsAlpha ; 
 void* TRUE ; 
 void* Verbose ; 
 int /*<<< orphan*/  Warning (char*) ; 
 int Width ; 
 double atof (void*) ; 
 void* atoi (void*) ; 
 int /*<<< orphan*/ * cInpProf ; 
 int /*<<< orphan*/ * cOutProf ; 
 void* cProofing ; 
 void* lIsDeviceLink ; 
 int xgetopt (int,char**,char*) ; 
 void* xoptarg ; 

__attribute__((used)) static
void HandleSwitches(int argc, char *argv[])
{
    int s;

    while ((s=xgetopt(argc,argv,"aAeEbBw:W:nNvVGgh:H:i:I:o:O:P:p:t:T:c:C:l:L:M:m:K:k:S:s:D:d:")) != EOF) {

        switch (s) {

        case 'a':
        case 'A':
            StoreAsAlpha = TRUE;
            break;
        case 'b':
        case 'B':
            BlackWhiteCompensation = TRUE;
            break;

        case 'c':
        case 'C':
            PrecalcMode = atoi(xoptarg);
            if (PrecalcMode < 0 || PrecalcMode > 3)
                FatalError("Unknown precalc mode '%d'", PrecalcMode);
            break;

        case 'd':
        case 'D': ObserverAdaptationState = atof(xoptarg);
            if (ObserverAdaptationState < 0 ||
                ObserverAdaptationState > 1.0)
                Warning("Adaptation state should be 0..1");
            break;

        case 'e':
        case 'E':
            EmbedProfile = TRUE;
            break;

        case 'g':
        case 'G':
            GamutCheck = TRUE;
            break;

        case 'v':
        case 'V':
            Verbose = TRUE;
            break;

        case 'i':
        case 'I':
            if (lIsDeviceLink)
                FatalError("Device-link already specified");

            cInpProf = xoptarg;
            break;

        case 'o':
        case 'O':
            if (lIsDeviceLink)
                FatalError("Device-link already specified");

            cOutProf = xoptarg;
            break;

        case 'l':
        case 'L':
            if (cInpProf != NULL || cOutProf != NULL)
                FatalError("input/output profiles already specified");

            cInpProf = xoptarg;
            lIsDeviceLink = TRUE;
            break;

        case 'p':
        case 'P':
            cProofing = xoptarg;
            break;

        case 't':
        case 'T':
            Intent = atoi(xoptarg);
            break;

        case 'm':
        case 'M':
            ProofingIntent = atoi(xoptarg);
            break;

        case 'N':
        case 'n':
            IgnoreEmbedded = TRUE;
            break;

        case 'W':
        case 'w':
            Width = atoi(xoptarg);
            if (Width != 8 && Width != 16 && Width != 32)
                FatalError("Only 8, 16 and 32 bps are supported");
            break;

        case 'k':
        case 'K':
            InkLimit = atof(xoptarg);
            if (InkLimit < 0.0 || InkLimit > 400.0)
                FatalError("Ink limit must be 0%%..400%%");
            break;


        case 's':
        case 'S': SaveEmbedded = xoptarg;
            break;

        case 'H':
        case 'h':  {

            int a =  atoi(xoptarg);
            Help(a);
            }
            break;

        default:

            FatalError("Unknown option - run without args to see valid ones");
        }

    }
}