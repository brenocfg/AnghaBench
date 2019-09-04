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
typedef  int /*<<< orphan*/  DHGLRC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL sw_ShareLists(DHGLRC dhglrcSrc, DHGLRC dhglrcDst)
{
#if 0
    struct sw_context* sw_ctx_src = (struct sw_context*)dhglrcSrc;
    struct sw_context* sw_ctx_dst = (struct sw_context*)dhglrcDst;
    
    /* See if it was already shared */
    if(sw_ctx_dst->gl_ctx->Shared->RefCount > 1)
        return FALSE;

    /* Unreference the old, share the new */
    gl_reference_shared_state(sw_ctx_dst->gl_ctx,
        &sw_ctx_dst->gl_ctx->Shared,
        sw_ctx_src->gl_ctx->Shared);
#endif
    FIXME("Unimplemented!\n");
    return TRUE;
}