#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  void* cmsFloat32Number ;
struct TYPE_10__ {double Y; void* y; void* x; } ;
struct TYPE_9__ {double Y; void* y; void* x; } ;
struct TYPE_8__ {double Y; void* y; void* x; } ;
struct TYPE_11__ {TYPE_3__ Blue; TYPE_2__ Green; TYPE_1__ Red; } ;
typedef  TYPE_4__ cmsCIExyYTRIPLE ;
struct TYPE_12__ {double Y; void* y; void* x; } ;
typedef  TYPE_5__ cmsCIExyY ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 scalar_t__ IgnoreEmbedded ; 
 int /*<<< orphan*/  PrintProfileInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SaveEmbedded ; 
 int /*<<< orphan*/  SaveMemoryBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFGetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void***,...) ; 
 int /*<<< orphan*/  TIFFGetFieldDefaulted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TIFFTAG_ICCPROFILE ; 
 int /*<<< orphan*/  TIFFTAG_PRIMARYCHROMATICITIES ; 
 int /*<<< orphan*/  TIFFTAG_TRANSFERFUNCTION ; 
 int /*<<< orphan*/  TIFFTAG_WHITEPOINT ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateRGBProfileTHR (int /*<<< orphan*/ *,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromMem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
cmsHPROFILE GetTIFFProfile(TIFF* in)
{
    cmsCIExyYTRIPLE Primaries;
    cmsFloat32Number* chr;
    cmsCIExyY WhitePoint;
    cmsFloat32Number* wp;
    int i;
    cmsToneCurve* Curve[3];
    cmsUInt16Number *gmr, *gmg, *gmb;
    cmsHPROFILE hProfile;
    cmsUInt32Number EmbedLen;
    cmsUInt8Number* EmbedBuffer;

    if (IgnoreEmbedded) return NULL;

    if (TIFFGetField(in, TIFFTAG_ICCPROFILE, &EmbedLen, &EmbedBuffer)) {

        hProfile = cmsOpenProfileFromMem(EmbedBuffer, EmbedLen);

        // Print description found in the profile
        if (Verbose && (hProfile != NULL)) {

            fprintf(stdout, "\n[Embedded profile]\n");
            PrintProfileInformation(NULL, hProfile);
            fflush(stdout);
        }

        if (hProfile != NULL && SaveEmbedded != NULL)
            SaveMemoryBlock(EmbedBuffer, EmbedLen, SaveEmbedded);

        if (hProfile) return hProfile;
    }

    // Try to see if "colorimetric" tiff

    if (TIFFGetField(in, TIFFTAG_PRIMARYCHROMATICITIES, &chr)) {

        Primaries.Red.x   =  chr[0];
        Primaries.Red.y   =  chr[1];
        Primaries.Green.x =  chr[2];
        Primaries.Green.y =  chr[3];
        Primaries.Blue.x  =  chr[4];
        Primaries.Blue.y  =  chr[5];

        Primaries.Red.Y = Primaries.Green.Y = Primaries.Blue.Y = 1.0;

        if (TIFFGetField(in, TIFFTAG_WHITEPOINT, &wp)) {

            WhitePoint.x = wp[0];
            WhitePoint.y = wp[1];
            WhitePoint.Y = 1.0;

            // Transferfunction is a bit harder....

            TIFFGetFieldDefaulted(in, TIFFTAG_TRANSFERFUNCTION,
                &gmr,
                &gmg,
                &gmb);

            Curve[0] = cmsBuildTabulatedToneCurve16(NULL, 256, gmr);
            Curve[1] = cmsBuildTabulatedToneCurve16(NULL, 256, gmg);
            Curve[2] = cmsBuildTabulatedToneCurve16(NULL, 256, gmb);

            hProfile = cmsCreateRGBProfileTHR(NULL, &WhitePoint, &Primaries, Curve);

            for (i=0; i < 3; i++)
                cmsFreeToneCurve(NULL, Curve[i]);

            if (Verbose) {
                fprintf(stdout, "\n[Colorimetric TIFF]\n");
            }


            return hProfile;
        }
    }

    return NULL;
}