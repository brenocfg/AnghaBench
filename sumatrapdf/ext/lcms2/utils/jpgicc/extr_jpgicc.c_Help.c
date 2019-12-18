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
 double LCMS_VERSION ; 
 int /*<<< orphan*/  PrintBuiltins () ; 
 int /*<<< orphan*/  PrintRenderingIntents (int /*<<< orphan*/ *) ; 
 int SW ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void Help(int level)
{
     fprintf(stderr, "little cms ICC profile applier for JPEG - v3.2 [LittleCMS %2.2f]\n\n", LCMS_VERSION / 1000.0);

     switch(level) {

     default:
     case 0:

     fprintf(stderr, "usage: jpgicc [flags] input.jpg output.jpg\n");

     fprintf(stderr, "\nflags:\n\n");
     fprintf(stderr, "%cv - Verbose\n", SW);
     fprintf(stderr, "%ci<profile> - Input profile (defaults to sRGB)\n", SW);
     fprintf(stderr, "%co<profile> - Output profile (defaults to sRGB)\n", SW);

     PrintRenderingIntents(NULL);


     fprintf(stderr, "%cb - Black point compensation\n", SW);
     fprintf(stderr, "%cd<0..1> - Observer adaptation state (abs.col. only)\n", SW);
     fprintf(stderr, "%cn - Ignore embedded profile\n", SW);
     fprintf(stderr, "%ce - Embed destination profile\n", SW);
     fprintf(stderr, "%cs<new profile> - Save embedded profile as <new profile>\n", SW);

     fprintf(stderr, "\n");

     fprintf(stderr, "%cc<0,1,2,3> - Precalculates transform (0=Off, 1=Normal, 2=Hi-res, 3=LoRes) [defaults to 1]\n", SW);
     fprintf(stderr, "\n");

     fprintf(stderr, "%cp<profile> - Soft proof profile\n", SW);
     fprintf(stderr, "%cm<0,1,2,3> - SoftProof intent\n", SW);
     fprintf(stderr, "%cg - Marks out-of-gamut colors on softproof\n", SW);
     fprintf(stderr, "%c!<r>,<g>,<b> - Out-of-gamut marker channel values\n", SW);

     fprintf(stderr, "\n");
     fprintf(stderr, "%cq<0..100> - Output JPEG quality\n", SW);

     fprintf(stderr, "\n");
     fprintf(stderr, "%ch<0,1,2,3> - More help\n", SW);
     break;

     case 1:

     fprintf(stderr, "Examples:\n\n"
                     "To color correct from scanner to sRGB:\n"
                     "\tjpgicc %ciscanner.icm in.jpg out.jpg\n"
                     "To convert from monitor1 to monitor2:\n"
                     "\tjpgicc %cimon1.icm %comon2.icm in.jpg out.jpg\n"
                     "To make a CMYK separation:\n"
                     "\tjpgicc %coprinter.icm inrgb.jpg outcmyk.jpg\n"
                     "To recover sRGB from a CMYK separation:\n"
                     "\tjpgicc %ciprinter.icm incmyk.jpg outrgb.jpg\n"
                     "To convert from CIELab ITU/Fax JPEG to sRGB\n"
                     "\tjpgicc in.jpg out.jpg\n\n",
                     SW, SW, SW, SW, SW);
     break;

     case 2:
         PrintBuiltins();
         break;

     case 3:

     fprintf(stderr, "This program is intended to be a demo of the little cms\n"
                     "engine. Both lcms and this program are freeware. You can\n"
                     "obtain both in source code at http://www.littlecms.com\n"
                     "For suggestions, comments, bug reports etc. send mail to\n"
                     "marti@littlecms.com\n\n");
     break;
     }

     exit(0);
}