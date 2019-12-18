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
 int /*<<< orphan*/  PrintBuiltins () ; 
 int /*<<< orphan*/  PrintRenderingIntents (int /*<<< orphan*/ *) ; 
 int SW ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
int Help(int level)
{
     switch (level) {

     default:
     case 0:

         fprintf(stderr, "\nlinkicc: Links profiles into a single devicelink.\n");

         fprintf(stderr, "\n");
         fprintf(stderr, "usage: linkicc [flags] <profiles>\n\n");
         fprintf(stderr, "flags:\n\n");
         fprintf(stderr, "%co<profile> - Output devicelink profile. [defaults to 'devicelink.icc']\n", SW);

         PrintRenderingIntents(NULL);

         fprintf(stderr, "%cc<0,1,2> - Precision (0=LowRes, 1=Normal, 2=Hi-res) [defaults to 1]\n", SW);
         fprintf(stderr, "%cn<gridpoints> - Alternate way to set precision, number of CLUT points\n", SW);
         fprintf(stderr, "%cd<description> - description text (quotes can be used)\n", SW);
         fprintf(stderr, "%cy<copyright> - copyright notice (quotes can be used)\n", SW);

         fprintf(stderr, "\n%ck<0..400> - Ink-limiting in %% (CMYK only)\n", SW);
         fprintf(stderr, "%c8 - Creates 8-bit devicelink\n", SW);
         fprintf(stderr, "%cx - Creatively, guess deviceclass of resulting profile.\n", SW);
         fprintf(stderr, "%cb - Black point compensation\n", SW);
         fprintf(stderr, "%ca<0..1> - Observer adaptation state (abs.col. only)\n\n", SW);
         fprintf(stderr, "%cl - Use linearization curves (may affect accuracy)\n", SW);
         fprintf(stderr, "%cr<v.r> - Profile version. (CAUTION: may change the profile implementation)\n", SW);
         fprintf(stderr, "\n");
         fprintf(stderr, "Colorspaces must be paired except Lab/XYZ, that can be interchanged.\n\n");

         fprintf(stderr, "%ch<0,1,2,3> - More help\n", SW);
         break;

     case 1:
         PrintBuiltins();
         break;

     case 2:

         fprintf(stderr, "\nExamples:\n\n"
             "To create 'devicelink.icm' from a.icc to b.icc:\n"
             "\tlinkicc a.icc b.icc\n\n"
             "To create 'out.icc' from sRGB to cmyk.icc:\n"
             "\tlinkicc -o out.icc *sRGB cmyk.icc\n\n"
             "To create a sRGB input profile working in Lab:\n"
             "\tlinkicc -x -o sRGBLab.icc *sRGB *Lab\n\n"
             "To create a XYZ -> sRGB output profile:\n"
             "\tlinkicc -x -o sRGBLab.icc *XYZ *sRGB\n\n"
             "To create a abstract profile doing softproof for cmyk.icc:\n"
             "\tlinkicc -t1 -x -o softproof.icc *Lab cmyk.icc cmyk.icc *Lab\n\n"
             "To create a 'grayer' sRGB input profile:\n"
             "\tlinkicc -x -o grayer.icc *sRGB gray.icc gray.icc *Lab\n\n"
             "To embed ink limiting into a cmyk output profile:\n"
             "\tlinkicc -x -o cmyklimited.icc -k 250 cmyk.icc *Lab\n\n");
         break;

     case 3:

         fprintf(stderr, "This program is intended to be a demo of the little cms\n"
             "engine. Both lcms and this program are freeware. You can\n"
             "obtain both in source code at http://www.littlecms.com\n"
             "For suggestions, comments, bug reports etc. send mail to\n"
             "info@littlecms.com\n\n");
    }

   exit(0);
}