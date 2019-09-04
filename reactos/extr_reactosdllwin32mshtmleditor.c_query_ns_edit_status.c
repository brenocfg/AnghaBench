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
typedef  int /*<<< orphan*/  nsICommandParams ;
typedef  scalar_t__ cpp_bool ;
struct TYPE_7__ {TYPE_2__* doc_obj; TYPE_1__* window; } ;
struct TYPE_6__ {scalar_t__ usermode; scalar_t__ nscontainer; } ;
struct TYPE_5__ {scalar_t__ readystate; } ;
typedef  TYPE_3__ HTMLDocument ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ EDITMODE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NSSTATE_ALL ; 
 int OLECMDF_ENABLED ; 
 int OLECMDF_LATCHED ; 
 int OLECMDF_SUPPORTED ; 
 scalar_t__ READYSTATE_INTERACTIVE ; 
 int /*<<< orphan*/ * create_nscommand_params () ; 
 int /*<<< orphan*/  get_ns_command_state (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_GetBooleanValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nsICommandParams_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD query_ns_edit_status(HTMLDocument *This, const char *nscmd)
{
    nsICommandParams *nsparam;
    cpp_bool b = FALSE;

    if(This->doc_obj->usermode != EDITMODE || This->window->readystate < READYSTATE_INTERACTIVE)
        return OLECMDF_SUPPORTED;

    if(This->doc_obj->nscontainer && nscmd) {
        nsparam = create_nscommand_params();
        get_ns_command_state(This->doc_obj->nscontainer, nscmd, nsparam);

        nsICommandParams_GetBooleanValue(nsparam, NSSTATE_ALL, &b);

        nsICommandParams_Release(nsparam);
    }

    return OLECMDF_SUPPORTED | OLECMDF_ENABLED | (b ? OLECMDF_LATCHED : 0);
}