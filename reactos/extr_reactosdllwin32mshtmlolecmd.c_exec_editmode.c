#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_4__ {int /*<<< orphan*/  doc_obj; } ;
typedef  TYPE_1__ HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_edit_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT exec_editmode(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    TRACE("(%p)->(%08x %p %p)\n", This, cmdexecopt, in, out);

    if(in || out)
        FIXME("unsupported args\n");

    return setup_edit_mode(This->doc_obj);
}