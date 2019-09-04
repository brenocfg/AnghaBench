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
struct sw_context {int /*<<< orphan*/  gl_ctx; } ;
typedef  int /*<<< orphan*/  GLDISPATCHTABLE ;
typedef  scalar_t__ DHGLRC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sw_context*) ; 
 int /*<<< orphan*/ * IntGetCurrentDispatchTable () ; 
 void* IntGetCurrentICDPrivate () ; 
 int /*<<< orphan*/  IntSetCurrentDispatchTable (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  IntSetCurrentICDPrivate (void*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gl_destroy_context (int /*<<< orphan*/ ) ; 

BOOL sw_DeleteContext(DHGLRC dhglrc)
{
    struct sw_context* sw_ctx = (struct sw_context*)dhglrc;
    /* Those get clobbered by _mesa_free_context_data via _glapi_set{context,dispath_table} */
    void* icd_save = IntGetCurrentICDPrivate();
    const GLDISPATCHTABLE* table_save = IntGetCurrentDispatchTable();
    
    /* Destroy everything */
    gl_destroy_context(sw_ctx->gl_ctx);

    HeapFree(GetProcessHeap(), 0, sw_ctx);
    
    /* Restore this */
    IntSetCurrentDispatchTable(table_save);
    IntSetCurrentICDPrivate(icd_save);

    return TRUE;
}