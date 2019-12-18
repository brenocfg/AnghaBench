#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ cmsVEC3 ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsCreateProfilePlaceholder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsD50_XYZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetHeaderRenderingIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsSigBToD1Tag ; 
 int /*<<< orphan*/  cmsSigColorSpaceClass ; 
 int /*<<< orphan*/  cmsSigDToB1Tag ; 
 int /*<<< orphan*/  cmsSigMediaWhitePointTag ; 
 int /*<<< orphan*/  cmsSigXYZData ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsHPROFILE IdentityMatrixProfile( cmsColorSpaceSignature dataSpace)
{
    cmsContext ctx = 0;
    cmsVEC3 zero = {{0,0,0}};
    cmsMAT3 identity;
    cmsPipeline* forward;
    cmsPipeline* reverse;
    cmsHPROFILE identityProfile = cmsCreateProfilePlaceholder( ctx);


    cmsSetProfileVersion(DbgThread(), identityProfile, 4.3);

    cmsSetDeviceClass(DbgThread(),  identityProfile,     cmsSigColorSpaceClass);
    cmsSetColorSpace(DbgThread(), identityProfile,       dataSpace);
    cmsSetPCS(DbgThread(), identityProfile,              cmsSigXYZData);

    cmsSetHeaderRenderingIntent(DbgThread(), identityProfile,  INTENT_RELATIVE_COLORIMETRIC);

    cmsWriteTag(DbgThread(), identityProfile, cmsSigMediaWhitePointTag, cmsD50_XYZ(DbgThread()));



    _cmsMAT3identity(DbgThread(),  &identity);

    // build forward transform.... (RGB to PCS)
    forward = cmsPipelineAlloc( 0, 3, 3);
    cmsPipelineInsertStage(DbgThread(),  forward, cmsAT_END, cmsStageAllocMatrix( ctx, 3, 3, (cmsFloat64Number*)&identity, (cmsFloat64Number*)&zero));
    cmsWriteTag(DbgThread(),  identityProfile, cmsSigDToB1Tag, forward);

    cmsPipelineFree(DbgThread(), forward);

    reverse = cmsPipelineAlloc( 0, 3, 3);
    cmsPipelineInsertStage(DbgThread(),  reverse, cmsAT_END, cmsStageAllocMatrix( ctx, 3, 3, (cmsFloat64Number*)&identity, (cmsFloat64Number*)&zero));
    cmsWriteTag(DbgThread(),  identityProfile, cmsSigBToD1Tag, reverse);

    cmsPipelineFree(DbgThread(), reverse);

    return identityProfile;
}