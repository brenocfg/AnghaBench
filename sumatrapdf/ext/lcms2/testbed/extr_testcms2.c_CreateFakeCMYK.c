#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsBool ;
struct TYPE_3__ {void* hIlimit; void* sRGB2Lab; void* hLab2sRGB; } ;
typedef  TYPE_1__ FakeCMYKParams ;

/* Variables and functions */
 int BYTES_SH (int /*<<< orphan*/ ) ; 
 int CHANNELS_SH (int) ; 
 int /*<<< orphan*/ * Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int FLOAT_SH (int) ; 
 int /*<<< orphan*/  ForwardSampler ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  ReverseSampler ; 
 int TYPE_CMYK_16 ; 
 int TYPE_Lab_16 ; 
 int TYPE_RGB_DBL ; 
 int /*<<< orphan*/ * _cmsStageAllocIdentityCurves (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateInkLimitingDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProfilePlaceholder (int /*<<< orphan*/ ) ; 
 void* cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,void*) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsLinkTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsSigAToB0Tag ; 
 int /*<<< orphan*/  cmsSigAToB1Tag ; 
 int /*<<< orphan*/  cmsSigAToB2Tag ; 
 int /*<<< orphan*/  cmsSigBToA0Tag ; 
 int /*<<< orphan*/  cmsSigBToA1Tag ; 
 int /*<<< orphan*/  cmsSigBToA2Tag ; 
 int /*<<< orphan*/  cmsSigCmykData ; 
 int /*<<< orphan*/  cmsSigLabData ; 
 int /*<<< orphan*/  cmsSigOutputClass ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static
cmsHPROFILE CreateFakeCMYK(cmsFloat64Number InkLimit, cmsBool lUseAboveRGB)
{
    cmsHPROFILE hICC;
    cmsPipeline* AToB0, *BToA0;
    cmsStage* CLUT;
    cmsContext ContextID;
    FakeCMYKParams p;
    cmsHPROFILE hLab, hsRGB, hLimit;
    cmsUInt32Number cmykfrm;

    ContextID = DbgThread();

    if (lUseAboveRGB)
        hsRGB = Create_AboveRGB();
    else
       hsRGB  = cmsCreate_sRGBProfile(ContextID);

    hLab   = cmsCreateLab4Profile(ContextID, NULL);
    hLimit = cmsCreateInkLimitingDeviceLink(ContextID, cmsSigCmykData, InkLimit);

    cmykfrm = FLOAT_SH(1) | BYTES_SH(0)|CHANNELS_SH(4);
    p.hLab2sRGB = cmsCreateTransform(ContextID, hLab,  TYPE_Lab_16,  hsRGB, TYPE_RGB_DBL, INTENT_PERCEPTUAL, cmsFLAGS_NOOPTIMIZE|cmsFLAGS_NOCACHE);
    p.sRGB2Lab  = cmsCreateTransform(ContextID, hsRGB, TYPE_RGB_DBL, hLab,  TYPE_Lab_16,  INTENT_PERCEPTUAL, cmsFLAGS_NOOPTIMIZE|cmsFLAGS_NOCACHE);
    p.hIlimit   = cmsCreateTransform(ContextID, hLimit, cmykfrm, NULL, TYPE_CMYK_16, INTENT_PERCEPTUAL, cmsFLAGS_NOOPTIMIZE|cmsFLAGS_NOCACHE);

    cmsCloseProfile(ContextID, hLab); cmsCloseProfile(ContextID, hsRGB); cmsCloseProfile(ContextID, hLimit);

    hICC = cmsCreateProfilePlaceholder(ContextID);
    if (!hICC) return NULL;

    cmsSetProfileVersion(ContextID, hICC, 4.3);

    cmsSetDeviceClass(ContextID, hICC, cmsSigOutputClass);
    cmsSetColorSpace(ContextID, hICC,  cmsSigCmykData);
    cmsSetPCS(ContextID, hICC,         cmsSigLabData);

    BToA0 = cmsPipelineAlloc(ContextID, 3, 4);
    if (BToA0 == NULL) return 0;
    CLUT = cmsStageAllocCLut16bit(ContextID, 17, 3, 4, NULL);
    if (CLUT == NULL) return 0;
    if (!cmsStageSampleCLut16bit(ContextID, CLUT, ForwardSampler, &p, 0)) return 0;

    cmsPipelineInsertStage(ContextID, BToA0, cmsAT_BEGIN, _cmsStageAllocIdentityCurves(ContextID, 3));
    cmsPipelineInsertStage(ContextID, BToA0, cmsAT_END, CLUT);
    cmsPipelineInsertStage(ContextID, BToA0, cmsAT_END, _cmsStageAllocIdentityCurves(ContextID, 4));

    if (!cmsWriteTag(ContextID, hICC, cmsSigBToA0Tag, (void*) BToA0)) return 0;
    cmsPipelineFree(ContextID, BToA0);

    AToB0 = cmsPipelineAlloc(ContextID, 4, 3);
    if (AToB0 == NULL) return 0;
    CLUT = cmsStageAllocCLut16bit(ContextID, 17, 4, 3, NULL);
    if (CLUT == NULL) return 0;
    if (!cmsStageSampleCLut16bit(ContextID, CLUT, ReverseSampler, &p, 0)) return 0;

    cmsPipelineInsertStage(ContextID, AToB0, cmsAT_BEGIN, _cmsStageAllocIdentityCurves(ContextID, 4));
    cmsPipelineInsertStage(ContextID, AToB0, cmsAT_END, CLUT);
    cmsPipelineInsertStage(ContextID, AToB0, cmsAT_END, _cmsStageAllocIdentityCurves(ContextID, 3));

    if (!cmsWriteTag(ContextID, hICC, cmsSigAToB0Tag, (void*) AToB0)) return 0;
    cmsPipelineFree(ContextID, AToB0);

    cmsDeleteTransform(ContextID, p.hLab2sRGB);
    cmsDeleteTransform(ContextID, p.sRGB2Lab);
    cmsDeleteTransform(ContextID, p.hIlimit);

    cmsLinkTag(ContextID, hICC, cmsSigAToB1Tag, cmsSigAToB0Tag);
    cmsLinkTag(ContextID, hICC, cmsSigAToB2Tag, cmsSigAToB0Tag);
    cmsLinkTag(ContextID, hICC, cmsSigBToA1Tag, cmsSigBToA0Tag);
    cmsLinkTag(ContextID, hICC, cmsSigBToA2Tag, cmsSigBToA0Tag);

    return hICC;
}