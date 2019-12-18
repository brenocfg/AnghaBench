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
 int /*<<< orphan*/  PrintRenderingIntents (int /*<<< orphan*/ *) ; 
 int SW ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void Help(void)
{

    fprintf(stderr, "usage: transicc [flags] [CGATS input] [CGATS output]\n\n");

    fprintf(stderr, "flags:\n\n");
    fprintf(stderr, "%cv<0..3> - Verbosity level\n", SW);

    fprintf(stderr, "%ce[op] - Encoded representation of numbers\n", SW);
    fprintf(stderr, "\t%cw - use 16 bits\n", SW);
    fprintf(stderr, "\t%cx - Hexadecimal\n\n", SW);

    fprintf(stderr, "%cs - bounded mode (clip negatives and highliths)\n", SW);
    fprintf(stderr, "%cq - Quantize (round decimals)\n\n", SW);

    fprintf(stderr, "%ci<profile> - Input profile (defaults to sRGB)\n", SW);
    fprintf(stderr, "%co<profile> - Output profile (defaults to sRGB)\n", SW);
    fprintf(stderr, "%cl<profile> - Transform by device-link profile\n", SW);

    fprintf(stderr, "\nYou can use '*Lab', '*xyz' and others as built-in profiles\n\n");

    PrintRenderingIntents(NULL);

    fprintf(stderr, "\n");

    fprintf(stderr, "%cd<0..1> - Observer adaptation state (abs.col. only)\n\n", SW);

    fprintf(stderr, "%cb - Black point compensation\n", SW);

    fprintf(stderr, "%cc<0,1,2,3> Precalculates transform (0=Off, 1=Normal, 2=Hi-res, 3=LoRes)\n\n", SW);
    fprintf(stderr, "%cn - Terse output, intended for pipe usage\n", SW);

    fprintf(stderr, "%cp<profile> - Soft proof profile\n", SW);
    fprintf(stderr, "%cm<0,1,2,3> - Soft proof intent\n", SW);
    fprintf(stderr, "%cg - Marks out-of-gamut colors on softproof\n\n", SW);



    fprintf(stderr, "This program is intended to be a demo of the little cms\n"
        "engine. Both lcms and this program are freeware. You can\n"
        "obtain both in source code at http://www.littlecms.com\n"
        "For suggestions, comments, bug reports etc. send mail to\n"
        "info@littlecms.com\n\n");
}