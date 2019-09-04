#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  scalar_t__ VARIANT_BOOL ;
struct TYPE_7__ {TYPE_1__* doc_obj; } ;
struct TYPE_6__ {int /*<<< orphan*/  editor; } ;
struct TYPE_5__ {scalar_t__ usermode; TYPE_2__* nscontainer; } ;
typedef  TYPE_3__ HTMLDocument ;

/* Variables and functions */
 scalar_t__ EDITMODE ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIEditor_IncrementModificationCount (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsIEditor_ResetModificationCount (int /*<<< orphan*/ ) ; 

void set_dirty(HTMLDocument *This, VARIANT_BOOL dirty)
{
    nsresult nsres;

    if(This->doc_obj->usermode != EDITMODE || !This->doc_obj->nscontainer || !This->doc_obj->nscontainer->editor)
        return;

    if(dirty) {
        nsres = nsIEditor_IncrementModificationCount(This->doc_obj->nscontainer->editor, 1);
        if(NS_FAILED(nsres))
            ERR("IncrementModificationCount failed: %08x\n", nsres);
    }else {
        nsres = nsIEditor_ResetModificationCount(This->doc_obj->nscontainer->editor);
        if(NS_FAILED(nsres))
            ERR("ResetModificationCount failed: %08x\n", nsres);
    }
}