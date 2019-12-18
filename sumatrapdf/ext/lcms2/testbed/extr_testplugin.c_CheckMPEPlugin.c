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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  double cmsFloat32Number ;
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * DupContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Fail (char*) ; 
 scalar_t__ IsGoodVal (char*,double,double,double) ; 
 int /*<<< orphan*/  MPEPluginSample ; 
 int /*<<< orphan*/  ResetFatalError (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StageAllocNegate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProfilePlaceholder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromMem (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cmsPipelineEvalFloat (int /*<<< orphan*/ *,double*,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmsSaveProfileToMem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  cmsSetLogErrorHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigDToB3Tag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 

cmsInt32Number CheckMPEPlugin(void)
{
    cmsContext ctx = NULL;
    cmsContext cpy = NULL;
    cmsHPROFILE h = NULL;
    cmsUInt32Number myTag = 1234;
    cmsUInt32Number rc = 0;
    char* data = NULL;
    cmsUInt32Number clen = 0;
    cmsFloat32Number In[3], Out[3];
    cmsPipeline* pipe;

    ctx = WatchDogContext(NULL);
    cmsPlugin(ctx, &MPEPluginSample);

    cpy =  DupContext(ctx, NULL);

    h = cmsCreateProfilePlaceholder(cpy);
    if (h == NULL) {
        Fail("Create placeholder failed");
        goto Error;
    }

    pipe = cmsPipelineAlloc(cpy, 3, 3);
    cmsPipelineInsertStage(cpy, pipe, cmsAT_BEGIN, StageAllocNegate(cpy));


    In[0] = 0.3f; In[1] = 0.2f; In[2] = 0.9f;
    cmsPipelineEvalFloat(cpy, In, Out, pipe);

    rc = (IsGoodVal("0", Out[0], 1.0-In[0], 0.001) &&
           IsGoodVal("1", Out[1], 1.0-In[1], 0.001) &&
           IsGoodVal("2", Out[2], 1.0-In[2], 0.001));

    if (!rc) {
        Fail("Pipeline failed");
        goto Error;
    }

    if (!cmsWriteTag(cpy, h, cmsSigDToB3Tag, pipe)) {
        Fail("Plug-in failed");
        goto Error;
    }

    // This cleans the stage as well
    cmsPipelineFree(cpy, pipe);

    rc = cmsSaveProfileToMem(cpy, h, NULL, &clen);
    if (!rc) {
        Fail("Fetch mem size failed");
        goto Error;
    }


    data = (char*) malloc(clen);
    if (data == NULL) {
        Fail("malloc failed ?!?");
        goto Error;
    }


    rc = cmsSaveProfileToMem(cpy, h, data, &clen);
    if (!rc) {
        Fail("Save to mem failed");
        goto Error;
    }

    cmsCloseProfile(cpy, h);

    cmsSetLogErrorHandler(cpy, NULL);
    h = cmsOpenProfileFromMem(cpy, data, clen);
    if (h == NULL) {
        Fail("Open profile failed");
        goto Error;
    }

    pipe = (cmsPipeline*) cmsReadTag(cpy, h, cmsSigDToB3Tag);
    if (pipe != NULL) {

        // Unsupported stage, should fail
        Fail("read tag/context switching failed");
        goto Error;
    }

    cmsCloseProfile(cpy, h);

    ResetFatalError(cpy);

    h = cmsOpenProfileFromMem(cpy, data, clen);
    if (h == NULL) {
        Fail("Open profile from mem failed");
        goto Error;
    }

    // Get rid of data
    free(data); data = NULL;

    pipe = (cmsPipeline*) cmsReadTag(cpy, h, cmsSigDToB3Tag);
    if (pipe == NULL) {
        Fail("Read tag/conext switching failed (2)");
        return 0;
    }

    // Evaluate for negation
    In[0] = 0.3f; In[1] = 0.2f; In[2] = 0.9f;
    cmsPipelineEvalFloat(cpy, In, Out, pipe);

     rc = (IsGoodVal("0", Out[0], 1.0-In[0], 0.001) &&
           IsGoodVal("1", Out[1], 1.0-In[1], 0.001) &&
           IsGoodVal("2", Out[2], 1.0-In[2], 0.001));

    cmsCloseProfile(cpy, h);
    cmsDeleteContext(ctx);
    cmsDeleteContext(cpy);
    return rc;

Error:

    if (h != NULL) cmsCloseProfile(ctx, h);
    if (ctx != NULL) cmsDeleteContext(ctx);
    if (cpy != NULL) cmsDeleteContext(cpy);
    if (data) free(data);

    return 0;
}