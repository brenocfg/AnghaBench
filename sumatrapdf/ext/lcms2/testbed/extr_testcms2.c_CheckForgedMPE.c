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
typedef  double cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  scalar_t__ cmsColorSpaceSignature ;

/* Variables and functions */
 size_t BYTES_SH (int) ; 
 size_t CHANNELS_SH (size_t) ; 
 size_t COLORSPACE_SH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  ErrorReportingFunction ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FatalErrorQuit ; 
 int /*<<< orphan*/  PT_ANY ; 
 int /*<<< orphan*/  PT_Lab ; 
 int /*<<< orphan*/  TYPE_BGR_8 ; 
 scalar_t__ T_BYTES (size_t) ; 
 scalar_t__ TrappedError ; 
 size_t cmsChannelsOf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*,int) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSetLogErrorHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsSigLabData ; 

__attribute__((used)) static
int CheckForgedMPE(void)
{
    cmsUInt32Number i;
    cmsHPROFILE srcProfile;
    cmsHPROFILE dstProfile;
    cmsColorSpaceSignature srcCS;
    cmsUInt32Number nSrcComponents;
    cmsUInt32Number srcFormat;
    cmsUInt32Number intent = 0;
    cmsUInt32Number flags = 0;
    cmsHTRANSFORM hTransform;
    cmsUInt8Number output[4];

    srcProfile = cmsOpenProfileFromFile(DbgThread(), "bad_mpe.icc", "r");
    if (!srcProfile)
        return 0;

    dstProfile = cmsCreate_sRGBProfile(DbgThread());
    if (!dstProfile) {
        cmsCloseProfile(DbgThread(), srcProfile);
        return 0;
    }

    srcCS = cmsGetColorSpace(DbgThread(), srcProfile);
    nSrcComponents = cmsChannelsOf(DbgThread(), srcCS);

    if (srcCS == cmsSigLabData) {
        srcFormat =
            COLORSPACE_SH(PT_Lab) | CHANNELS_SH(nSrcComponents) | BYTES_SH(0);
    }
    else {
        srcFormat =
            COLORSPACE_SH(PT_ANY) | CHANNELS_SH(nSrcComponents) | BYTES_SH(1);
    }

    cmsSetLogErrorHandler(DbgThread(), ErrorReportingFunction);

    hTransform = cmsCreateTransform(DbgThread(), srcProfile, srcFormat, dstProfile,
        TYPE_BGR_8, intent, flags);
    cmsCloseProfile(DbgThread(), srcProfile);
    cmsCloseProfile(DbgThread(), dstProfile);

    cmsSetLogErrorHandler(DbgThread(), FatalErrorQuit);

    // Should report error
    if (!TrappedError) return 0;

    TrappedError = FALSE;

    // Transform should NOT be created
    if (!hTransform) return 1;

    // Never should reach here
    if (T_BYTES(srcFormat) == 0) {  // 0 means double
        double input[128];
        for (i = 0; i < nSrcComponents; i++)
            input[i] = 0.5f;
        cmsDoTransform(DbgThread(), hTransform, input, output, 1);
    }
    else {
        cmsUInt8Number input[128];
        for (i = 0; i < nSrcComponents; i++)
            input[i] = 128;
        cmsDoTransform(DbgThread(), hTransform, input, output, 1);
    }
    cmsDeleteTransform(DbgThread(), hTransform);

    return 0;
}