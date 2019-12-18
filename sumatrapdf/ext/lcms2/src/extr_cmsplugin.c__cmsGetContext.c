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
struct _cmsContext_struct {struct _cmsContext_struct* Next; } ;
typedef  scalar_t__ cmsContext ;

/* Variables and functions */
 struct _cmsContext_struct* _cmsContextPoolHead ; 
 struct _cmsContext_struct globalContext ; 

struct _cmsContext_struct* _cmsGetContext(cmsContext ContextID)
{
    struct _cmsContext_struct* id = (struct _cmsContext_struct*) ContextID;
    struct _cmsContext_struct* ctx;


    // On 0, use global settings
    if (id == NULL)
        return &globalContext;

    // Search
    for (ctx = _cmsContextPoolHead;
         ctx != NULL;
         ctx = ctx ->Next) {

            // Found it?
            if (id == ctx)
                return ctx; // New-style context,
    }

    return &globalContext;
}