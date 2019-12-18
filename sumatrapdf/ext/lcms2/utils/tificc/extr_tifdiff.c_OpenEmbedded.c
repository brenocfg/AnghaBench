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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  GetInputPixelType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  PrintProfileInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TIFFGetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TIFFTAG_ICCPROFILE ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromMem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hLab ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
cmsUInt32Number OpenEmbedded(TIFF* tiff, cmsHPROFILE* PtrProfile, cmsHTRANSFORM* PtrXform)
{

    cmsUInt32Number EmbedLen, dwFormat = 0;
    cmsUInt8Number* EmbedBuffer;

    *PtrProfile = NULL;
    *PtrXform   = NULL;

    if (TIFFGetField(tiff, TIFFTAG_ICCPROFILE, &EmbedLen, &EmbedBuffer)) {

              *PtrProfile = cmsOpenProfileFromMem(EmbedBuffer, EmbedLen);

              if (Verbose) {

				  fprintf(stdout, "Embedded profile found:\n");
				  PrintProfileInformation(NULL, *PtrProfile);

              }

              dwFormat  = GetInputPixelType(tiff);
              *PtrXform = cmsCreateTransform(*PtrProfile, dwFormat,
                                          hLab, TYPE_Lab_DBL, INTENT_RELATIVE_COLORIMETRIC, 0);

      }

    return dwFormat;
}