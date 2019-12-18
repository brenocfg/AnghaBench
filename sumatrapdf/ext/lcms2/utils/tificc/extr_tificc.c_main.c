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
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleErrorHandler ; 
 int /*<<< orphan*/  ConsoleWarningHandler ; 
 int /*<<< orphan*/  FatalError (char*,char*) ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  Help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TIFFClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TIFFOpen (char*,char*) ; 
 scalar_t__ TIFFReadDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFSetErrorHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSetWarningHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TiffLabPlugin ; 
 int /*<<< orphan*/  TransformImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/  cInpProf ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int xoptind ; 

int main(int argc, char* argv[])
{
    TIFF *in, *out;

    cmsPlugin(&TiffLabPlugin);

    InitUtils(NULL, "tificc");

    HandleSwitches(argc, argv);

    if ((argc - xoptind) != 2) {

        Help(0);
    }


    TIFFSetErrorHandler(ConsoleErrorHandler);
    TIFFSetWarningHandler(ConsoleWarningHandler);

    in = TIFFOpen(argv[xoptind], "r");
    if (in == NULL) FatalError("Unable to open '%s'", argv[xoptind]);

    out = TIFFOpen(argv[xoptind+1], "w");

    if (out == NULL) {

        TIFFClose(in);
        FatalError("Unable to write '%s'", argv[xoptind+1]);
    }

    do {

        TransformImage(in, out, cInpProf);


    } while (TIFFReadDirectory(in));


    if (Verbose) { fprintf(stdout, "\n"); fflush(stdout); }

    TIFFClose(in);
    TIFFClose(out);

    return 0;
}