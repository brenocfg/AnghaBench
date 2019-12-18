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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  CGATSoutFilename ; 
 int /*<<< orphan*/  CloseTransforms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HandleSwitches (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 double LCMS_VERSION ; 
 int /*<<< orphan*/  OpenCGATSFiles (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  OpenTransforms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintEncodedResults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintFloatResults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintPCSEncoded (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintPCSFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PutCGATSValues (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TakeCGATSValues (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TakeFloatValues (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Verbose ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmsIT8Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIT8SaveToFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmsMAXCHANNELS ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,double) ; 
 int /*<<< orphan*/ * hIT8in ; 
 int /*<<< orphan*/ * hIT8out ; 
 int /*<<< orphan*/  hTrans ; 
 scalar_t__ lIsFloat ; 
 int nMaxPatches ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

int main(int argc, char *argv[])
{
    cmsUInt16Number Output[cmsMAXCHANNELS];
    cmsFloat64Number OutputFloat[cmsMAXCHANNELS];
    cmsFloat64Number InputFloat[cmsMAXCHANNELS];
    cmsContext ContextID =  NULL;

    int nPatch = 0;

    fprintf(stderr, "LittleCMS ColorSpace conversion calculator - 4.3 [LittleCMS %2.2f]\n", LCMS_VERSION / 1000.0);

    InitUtils(ContextID, "transicc");

    Verbose = 1;

    if (argc == 1) {

        Help();
        return 0;
    }

    HandleSwitches(ContextID, argc, argv);

    // Open profiles, create transforms
    if (!OpenTransforms(ContextID)) return 1;

    // Open CGATS input if specified
    OpenCGATSFiles(ContextID, argc, argv);

    // Main loop: read all values and convert them
    for(;;) {

        if (hIT8in != NULL) {

            if (nPatch >= nMaxPatches) break;
            TakeCGATSValues(ContextID, nPatch++, InputFloat);

        } else {

            if (feof(stdin)) break;
            TakeFloatValues(ContextID, InputFloat);

        }

        if (lIsFloat)
            cmsDoTransform(ContextID, hTrans, InputFloat, OutputFloat, 1);
        else
            cmsDoTransform(ContextID, hTrans, InputFloat, Output, 1);


        if (hIT8out != NULL) {

            PutCGATSValues(ContextID, OutputFloat);
        }
        else {

            if (lIsFloat) {
                PrintFloatResults(ContextID, OutputFloat); PrintPCSFloat(ContextID, InputFloat);
            }
            else {
                PrintEncodedResults(ContextID, Output);   PrintPCSEncoded(ContextID, InputFloat);
            }

        }
    }


    // Cleanup
    CloseTransforms(ContextID);

    if (hIT8in)
        cmsIT8Free(ContextID, hIT8in);

    if (hIT8out) {
        cmsIT8SaveToFile(ContextID, hIT8out, CGATSoutFilename);
        cmsIT8Free(ContextID, hIT8out);
    }

    // All is ok
    return 0;
}