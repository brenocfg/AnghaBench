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
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateInkLimitingDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsLinkTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * cmsPipelineDup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineUnlinkStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ cmsSigAToB0Tag ; 
 int /*<<< orphan*/  cmsSigAToB1Tag ; 
 int /*<<< orphan*/  cmsSigCmykData ; 
 scalar_t__ cmsTagLinkedTo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int CheckLinking(void)
{
    cmsHPROFILE h;
    cmsPipeline * pipeline;
    cmsStage *stageBegin, *stageEnd;

    // Create a CLUT based profile
     h = cmsCreateInkLimitingDeviceLink(DbgThread(), cmsSigCmykData, 150);

     // link a second tag
     cmsLinkTag(DbgThread(), h, cmsSigAToB1Tag, cmsSigAToB0Tag);

     // Save the linked devicelink
    if (!cmsSaveProfileToFile(DbgThread(), h, "lcms2link.icc")) return 0;
    cmsCloseProfile(DbgThread(), h);

    // Now open the profile and read the pipeline
    h = cmsOpenProfileFromFile(DbgThread(), "lcms2link.icc", "r");
    if (h == NULL) return 0;

    pipeline = (cmsPipeline*) cmsReadTag(DbgThread(), h, cmsSigAToB1Tag);
    if (pipeline == NULL)
    {
        return 0;
    }

    pipeline = cmsPipelineDup(DbgThread(), pipeline);

    // extract stage from pipe line
    cmsPipelineUnlinkStage(DbgThread(), pipeline, cmsAT_BEGIN, &stageBegin);
    cmsPipelineUnlinkStage(DbgThread(), pipeline, cmsAT_END,   &stageEnd);
    cmsPipelineInsertStage(DbgThread(), pipeline, cmsAT_END,    stageEnd);
    cmsPipelineInsertStage(DbgThread(), pipeline, cmsAT_BEGIN,  stageBegin);

    if (cmsTagLinkedTo(DbgThread(), h, cmsSigAToB1Tag) != cmsSigAToB0Tag) return 0;

    cmsWriteTag(DbgThread(), h, cmsSigAToB0Tag, pipeline);
    cmsPipelineFree(DbgThread(), pipeline);

    if (!cmsSaveProfileToFile(DbgThread(), h, "lcms2link2.icc")) return 0;
    cmsCloseProfile(DbgThread(), h);


    return 1;

}