#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double Min; double Peak; scalar_t__ n; } ;

/* Variables and functions */
 int /*<<< orphan*/  AssureShortTagIs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ CGATSout ; 
 int /*<<< orphan*/  ClearStatistics (TYPE_1__*) ; 
 int /*<<< orphan*/  CmpImages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ColorantStat ; 
 TYPE_1__ ColorimetricStat ; 
 int /*<<< orphan*/  ConsoleErrorHandler ; 
 int /*<<< orphan*/  ConsoleWarningHandler ; 
 int /*<<< orphan*/  CreateCGATS (char*,char*) ; 
 int /*<<< orphan*/  EqualLongTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EqualShortTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ EuclideanStat ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 double Mean (TYPE_1__*) ; 
 int PLANARCONFIG_CONTIG ; 
 double Std (TYPE_1__*) ; 
 int /*<<< orphan*/  TIFFClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TIFFOpen (char*,char*) ; 
 int /*<<< orphan*/  TIFFSetErrorHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFSetWarningHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFTAG_BITSPERSAMPLE ; 
 int /*<<< orphan*/  TIFFTAG_IMAGELENGTH ; 
 int /*<<< orphan*/  TIFFTAG_IMAGEWIDTH ; 
 int /*<<< orphan*/  TIFFTAG_PLANARCONFIG ; 
 int /*<<< orphan*/  TIFFTAG_SAMPLESPERPIXEL ; 
 int /*<<< orphan*/ * Tiff1 ; 
 int /*<<< orphan*/ * Tiff2 ; 
 int /*<<< orphan*/ * TiffDiff ; 
 char* TiffDiffFilename ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ cmsCreateLab4Profile (int /*<<< orphan*/ *) ; 
 scalar_t__ hLab ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,double) ; 
 int xoptind ; 

int main(int argc, char* argv[])
{
      int i;

      Tiff1 = Tiff2 = TiffDiff = NULL;

      InitUtils(NULL, "tiffdiff");

      HandleSwitches(argc, argv);

      if ((argc - xoptind) != 2) {

              Help();
              }

      TIFFSetErrorHandler(ConsoleErrorHandler);
      TIFFSetWarningHandler(ConsoleWarningHandler);

      Tiff1 = TIFFOpen(argv[xoptind], "r");
      if (Tiff1 == NULL) FatalError("Unable to open '%s'", argv[xoptind]);

      Tiff2 = TIFFOpen(argv[xoptind+1], "r");
      if (Tiff2 == NULL) FatalError("Unable to open '%s'", argv[xoptind+1]);

      if (TiffDiffFilename) {

          TiffDiff = TIFFOpen(TiffDiffFilename, "w");
          if (TiffDiff == NULL) FatalError("Unable to create '%s'", TiffDiffFilename);

      }


      AssureShortTagIs(Tiff1, Tiff2, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG, "Planar Config");
      AssureShortTagIs(Tiff1, Tiff2, TIFFTAG_BITSPERSAMPLE, 8, "8 bit per sample");

      EqualLongTag(Tiff1, Tiff2, TIFFTAG_IMAGEWIDTH,  "Image width");
      EqualLongTag(Tiff1, Tiff2, TIFFTAG_IMAGELENGTH, "Image length");

      EqualShortTag(Tiff1, Tiff2, TIFFTAG_SAMPLESPERPIXEL, "Samples per pixel");


      hLab = cmsCreateLab4Profile(NULL);

      ClearStatistics(&EuclideanStat);
      for (i=0; i < 4; i++)
            ClearStatistics(&ColorantStat[i]);

      if (!CmpImages(Tiff1, Tiff2, TiffDiff))
                FatalError("Error comparing images");

      if (CGATSout) {
            CreateCGATS(argv[xoptind], argv[xoptind+1]);
      }
      else {

        double  Per100 = 100.0 * ((255.0 - Mean(&EuclideanStat)) / 255.0);

        printf("Digital counts  %g%% equal. mean %g, min %g, max %g, Std %g\n", Per100, Mean(&EuclideanStat),
                                                                                EuclideanStat.Min,
                                                                                EuclideanStat.Peak,
                                                                                Std(&EuclideanStat));

        if (ColorimetricStat.n > 0) {

            Per100 = 100.0 * ((255.0 - Mean(&ColorimetricStat)) / 255.0);

            printf("dE Colorimetric %g%% equal. mean %g, min %g, max %g, Std %g\n", Per100, Mean(&ColorimetricStat),
                                                                                    ColorimetricStat.Min,
                                                                                    ColorimetricStat.Peak,
                                                                                    Std(&ColorimetricStat));
        }

      }

      if (hLab)     cmsCloseProfile(NULL, hLab);
      if (Tiff1)    TIFFClose(Tiff1);
      if (Tiff2)    TIFFClose(Tiff2);
      if (TiffDiff) TIFFClose(TiffDiff);

      return 0;
}