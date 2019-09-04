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
struct TYPE_5__ {int /*<<< orphan*/  usermode; } ;
typedef  TYPE_2__ HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BROWSEMODE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT exec_browsemode(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    WARN("(%p)->(%08x %p %p)\n", This, cmdexecopt, in, out);

    if(in || out)
        FIXME("unsupported args\n");

    This->doc_obj->usermode = BROWSEMODE;

    return S_OK;
}