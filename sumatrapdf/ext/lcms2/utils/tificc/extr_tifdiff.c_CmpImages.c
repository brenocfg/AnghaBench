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
typedef  int uint16 ;
typedef  scalar_t__ cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  scalar_t__ cmsHTRANSFORM ;
typedef  scalar_t__ cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsCIELab ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  AddOnePixel (int /*<<< orphan*/ *,double) ; 
 int COMPRESSION_NONE ; 
 int Channels ; 
 int /*<<< orphan*/ * ColorantStat ; 
 int /*<<< orphan*/  ColorimetricStat ; 
 int /*<<< orphan*/  EuclideanStat ; 
 int /*<<< orphan*/  FatalError (char*,int) ; 
 int /*<<< orphan*/  OpenEmbedded (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
#define  PHOTOMETRIC_MINISBLACK 131 
#define  PHOTOMETRIC_MINISWHITE 130 
#define  PHOTOMETRIC_RGB 129 
#define  PHOTOMETRIC_SEPARATED 128 
 int PLANARCONFIG_CONTIG ; 
 int PixelSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFGetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ TIFFReadScanline (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFFScanlineSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFSetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TIFFTAG_BITSPERSAMPLE ; 
 int /*<<< orphan*/  TIFFTAG_COMPRESSION ; 
 int /*<<< orphan*/  TIFFTAG_IMAGELENGTH ; 
 int /*<<< orphan*/  TIFFTAG_IMAGEWIDTH ; 
 int /*<<< orphan*/  TIFFTAG_PHOTOMETRIC ; 
 int /*<<< orphan*/  TIFFTAG_PLANARCONFIG ; 
 int /*<<< orphan*/  TIFFTAG_SAMPLESPERPIXEL ; 
 int /*<<< orphan*/  TIFFWriteDirectory (int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFWriteScanline (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TIFFfree (scalar_t__*) ; 
 scalar_t__ _TIFFmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *,scalar_t__) ; 
 double cmsDeltaE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 double fabs (scalar_t__) ; 
 scalar_t__ floor (double) ; 
 int sqrt (double) ; 

__attribute__((used)) static
int CmpImages(TIFF* tiff1, TIFF* tiff2, TIFF* diff)
{
    cmsUInt8Number* buf1, *buf2, *buf3=NULL;
    int row, cols, imagewidth = 0, imagelength = 0;
    uint16   Photometric;
    double dE = 0;
    double dR, dG, dB, dC, dM, dY, dK;
    int rc = 0;
    cmsHPROFILE hProfile1 = 0, hProfile2 = 0;
    cmsHTRANSFORM xform1 = 0, xform2 = 0;
    cmsUInt32Number dwFormat1, dwFormat2;



      TIFFGetField(tiff1, TIFFTAG_PHOTOMETRIC, &Photometric);
      TIFFGetField(tiff1, TIFFTAG_IMAGEWIDTH,  &imagewidth);
      TIFFGetField(tiff1, TIFFTAG_IMAGELENGTH, &imagelength);
      TIFFGetField(tiff1, TIFFTAG_SAMPLESPERPIXEL, &Channels);

      dwFormat1 = OpenEmbedded(tiff1, &hProfile1, &xform1);
      dwFormat2 = OpenEmbedded(tiff2, &hProfile2, &xform2);



      buf1 = (cmsUInt8Number*)_TIFFmalloc(TIFFScanlineSize(tiff1));
      buf2 = (cmsUInt8Number*)_TIFFmalloc(TIFFScanlineSize(tiff2));

      if (diff) {

           TIFFSetField(diff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
           TIFFSetField(diff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
           TIFFSetField(diff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

           TIFFSetField(diff, TIFFTAG_IMAGEWIDTH,  imagewidth);
           TIFFSetField(diff, TIFFTAG_IMAGELENGTH, imagelength);

           TIFFSetField(diff, TIFFTAG_SAMPLESPERPIXEL, 1);
           TIFFSetField(diff, TIFFTAG_BITSPERSAMPLE, 8);

           buf3 = (cmsUInt8Number*)_TIFFmalloc(TIFFScanlineSize(diff));
      }



      for (row = 0; row < imagelength; row++) {

        if (TIFFReadScanline(tiff1, buf1, row, 0) < 0) goto Error;
        if (TIFFReadScanline(tiff2, buf2, row, 0) < 0) goto Error;


        for (cols = 0; cols < imagewidth; cols++) {


            switch (Photometric) {

            case PHOTOMETRIC_MINISWHITE:
            case PHOTOMETRIC_MINISBLACK:

                    dE = fabs(buf2[cols] - buf1[cols]);

                    AddOnePixel(&ColorantStat[0], dE);
                    AddOnePixel(&EuclideanStat, dE);
                    break;

            case PHOTOMETRIC_RGB:

                    {
                        int index = 3 * cols;

                        dR = fabs(buf2[index+0] - buf1[index+0]);
                        dG = fabs(buf2[index+1] - buf1[index+1]);
                        dB = fabs(buf2[index+2] - buf1[index+2]);

                        dE = sqrt(dR * dR + dG * dG + dB * dB) / sqrt(3.);
                    }

                    AddOnePixel(&ColorantStat[0], dR);
                    AddOnePixel(&ColorantStat[1], dG);
                    AddOnePixel(&ColorantStat[2], dB);
                    AddOnePixel(&EuclideanStat,   dE);
                    break;

            case PHOTOMETRIC_SEPARATED:

                {
                        int index = 4 * cols;

                        dC = fabs(buf2[index+0] - buf1[index+0]);
                        dM = fabs(buf2[index+1] - buf1[index+1]);
                        dY = fabs(buf2[index+2] - buf1[index+2]);
                        dK = fabs(buf2[index+3] - buf1[index+3]);

                        dE = sqrt(dC * dC + dM * dM + dY * dY + dK * dK) / 2.;
                    }
                    AddOnePixel(&ColorantStat[0], dC);
                    AddOnePixel(&ColorantStat[1], dM);
                    AddOnePixel(&ColorantStat[2], dY);
                    AddOnePixel(&ColorantStat[3], dK);
                    AddOnePixel(&EuclideanStat,   dE);
                    break;

            default:
                    FatalError("Unsupported channels: %d", Channels);
            }


            if (xform1 && xform2) {


                cmsCIELab Lab1, Lab2;
                size_t index1 = cols * PixelSize(dwFormat1);
                size_t index2 = cols * PixelSize(dwFormat2);

                cmsDoTransform(NULL, xform1, &buf1[index1], &Lab1,  1);
                cmsDoTransform(NULL, xform2, &buf2[index2], &Lab2,  1);

                dE = cmsDeltaE(NULL, &Lab1, &Lab2);
                AddOnePixel(&ColorimetricStat, dE);
            }


            if (diff) {
                buf3[cols] = (cmsUInt8Number) floor(dE + 0.5);
        }

        }

        if (diff) {

                if (TIFFWriteScanline(diff, buf3, row, 0) < 0) goto Error;
        }


      }

     rc = 1;

Error:

     if (hProfile1) cmsCloseProfile(NULL, hProfile1);
     if (hProfile2) cmsCloseProfile(NULL, hProfile2);
     if (xform1) cmsDeleteTransform(NULL, xform1);
     if (xform2) cmsDeleteTransform(NULL, xform2);
      _TIFFfree(buf1); _TIFFfree(buf2);
      if (diff) {
           TIFFWriteDirectory(diff);
          if (buf3 != NULL) _TIFFfree(buf3);
      }
      return rc;
}