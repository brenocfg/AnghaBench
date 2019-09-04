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
typedef  int /*<<< orphan*/  nsICommandParams ;
struct TYPE_6__ {TYPE_1__* doc_obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  nscontainer; } ;
typedef  TYPE_2__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  NSCMD_ALIGN ; 
 int /*<<< orphan*/  NSSTATE_ATTRIBUTE ; 
 int /*<<< orphan*/ * create_nscommand_params () ; 
 int /*<<< orphan*/  do_ns_command (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsICommandParams_SetCStringValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void set_ns_align(HTMLDocument *This, const char *align_str)
{
    nsICommandParams *nsparam;

    if(!This->doc_obj->nscontainer)
        return;

    nsparam = create_nscommand_params();
    nsICommandParams_SetCStringValue(nsparam, NSSTATE_ATTRIBUTE, align_str);

    do_ns_command(This, NSCMD_ALIGN, nsparam);

    nsICommandParams_Release(nsparam);
}