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
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_6__ {TYPE_1__* doc_obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  nscontainer; } ;
typedef  TYPE_2__ HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  NSCMD_COPY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  UPDATE_UI ; 
 int /*<<< orphan*/  do_ns_editor_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_doc (TYPE_2__*,int /*<<< orphan*/ ) ; 

HRESULT editor_exec_copy(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    update_doc(This, UPDATE_UI);

    if(!This->doc_obj->nscontainer)
        return E_FAIL;

    do_ns_editor_command(This->doc_obj->nscontainer, NSCMD_COPY);
    return S_OK;
}