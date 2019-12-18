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
 int SW ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void Help(void)
{
	 fprintf(stderr, "little CMS ICC PostScript generator - v2.1 [LittleCMS %2.2f]\n", LCMS_VERSION / 1000.0);

     fprintf(stderr, "usage: psicc [flags] [<Output file>]\n\n");

     fprintf(stderr, "flags:\n\n");

     fprintf(stderr, "%ci<profile> - Input profile: Generates Color Space Array (CSA)\n", SW);
     fprintf(stderr, "%co<profile> - Output profile: Generates Color Rendering Dictionary(CRD)\n", SW);

     fprintf(stderr, "%ct<0,1,2,3> - Intent (0=Perceptual, 1=Colorimetric, 2=Saturation, 3=Absolute)\n", SW);

     fprintf(stderr, "%cb - Black point compensation (CRD only)\n", SW);
     fprintf(stderr, "%cu - Do NOT generate resource name on CRD\n", SW);
     fprintf(stderr, "%cc<0,1,2> - Precision (0=LowRes, 1=Normal (default), 2=Hi-res) (CRD only)\n", SW);
     fprintf(stderr, "%cn<gridpoints> - Alternate way to set precission, number of CLUT points (CRD only)\n", SW);

	 fprintf(stderr, "\n");
	 fprintf(stderr, "If no output file is specified, output goes to stdout.\n\n");
     fprintf(stderr, "This program is intended to be a demo of the little cms\n"
                     "engine. Both lcms and this program are freeware. You can\n"
                     "obtain both in source code at http://www.littlecms.com\n"
                     "For suggestions, comments, bug reports etc. send mail to\n"
                     "info@littlecms.com\n\n");
     exit(0);
}