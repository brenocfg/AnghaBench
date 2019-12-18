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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  InterpPluginSample ; 
 int /*<<< orphan*/  IsGoodWord (char*,int,int) ; 
 int /*<<< orphan*/ * WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cmsPipelineEval16 (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ *,int,int,int,int*) ; 

cmsInt32Number CheckInterp3DPlugin(void)
{

    cmsPipeline* p;
    cmsStage* clut;
    cmsContext ctx;
    cmsUInt16Number In[3], Out[3];
    cmsUInt16Number identity[] = {

       0,       0,       0,
       0,       0,       0xffff,
       0,       0xffff,  0,
       0,       0xffff,  0xffff,
       0xffff,  0,       0,
       0xffff,  0,       0xffff,
       0xffff,  0xffff,  0,
       0xffff,  0xffff,  0xffff
    };


    ctx = WatchDogContext(NULL);
    if (ctx == NULL) {
        Fail("Cannot create context");
       return 0;
    }

    cmsPlugin(ctx, &InterpPluginSample);

    p =  cmsPipelineAlloc(ctx, 3, 3);
    clut = cmsStageAllocCLut16bit(ctx, 2, 3, 3, identity);
    cmsPipelineInsertStage(ctx, p, cmsAT_BEGIN, clut);

    // Do some interpolations with the plugin

    In[0] = 0; In[1] = 0; In[2] = 0;
    cmsPipelineEval16(ctx, In, Out, p);

    if (!IsGoodWord("0", Out[0], 0xFFFF - 0)) goto Error;
    if (!IsGoodWord("1", Out[1], 0xFFFF - 0)) goto Error;
    if (!IsGoodWord("2", Out[2], 0xFFFF - 0)) goto Error;

    In[0] = 0x1234; In[1] = 0x5678; In[2] = 0x9ABC;
    cmsPipelineEval16(ctx, In, Out, p);

    if (!IsGoodWord("0", 0xFFFF - 0x9ABC, Out[0])) goto Error;
    if (!IsGoodWord("1", 0xFFFF - 0x5678, Out[1])) goto Error;
    if (!IsGoodWord("2", 0xFFFF - 0x1234, Out[2])) goto Error;

    cmsPipelineFree(ctx, p);
    cmsDeleteContext(ctx);

    // Now without the plug-in

    p =  cmsPipelineAlloc(NULL, 3, 3);
    clut = cmsStageAllocCLut16bit(NULL, 2, 3, 3, identity);
    cmsPipelineInsertStage(NULL, p, cmsAT_BEGIN, clut);

    In[0] = 0; In[1] = 0; In[2] = 0;
    cmsPipelineEval16(NULL, In, Out, p);

    if (!IsGoodWord("0", 0, Out[0])) goto Error;
    if (!IsGoodWord("1", 0, Out[1])) goto Error;
    if (!IsGoodWord("2", 0, Out[2])) goto Error;

    In[0] = 0x1234; In[1] = 0x5678; In[2] = 0x9ABC;
    cmsPipelineEval16(NULL, In, Out, p);

    if (!IsGoodWord("0", 0x1234, Out[0])) goto Error;
    if (!IsGoodWord("1", 0x5678, Out[1])) goto Error;
    if (!IsGoodWord("2", 0x9ABC, Out[2])) goto Error;

    cmsPipelineFree(NULL, p);
    return 1;

Error:
    cmsPipelineFree(NULL, p);
    return 0;
}