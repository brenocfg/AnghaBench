#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* named_items; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  disp; struct TYPE_6__* next; } ;
typedef  TYPE_2__ named_item_t ;
typedef  int /*<<< orphan*/  exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SCRIPTITEM_GLOBALMEMBERS ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  disp_get_id (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprval_set_disp_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL lookup_global_members(script_ctx_t *ctx, BSTR identifier, exprval_t *ret)
{
    named_item_t *item;
    DISPID id;
    HRESULT hres;

    for(item = ctx->named_items; item; item = item->next) {
        if(item->flags & SCRIPTITEM_GLOBALMEMBERS) {
            hres = disp_get_id(ctx, item->disp, identifier, identifier, 0, &id);
            if(SUCCEEDED(hres)) {
                if(ret)
                    exprval_set_disp_ref(ret, item->disp, id);
                return TRUE;
            }
        }
    }

    return FALSE;
}