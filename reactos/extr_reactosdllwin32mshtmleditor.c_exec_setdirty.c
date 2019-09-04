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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HTMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ VT_BOOL ; 
 int /*<<< orphan*/  V_BOOL (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT exec_setdirty(HTMLDocument *This, DWORD cmdexecopt, VARIANT *in, VARIANT *out)
{
    TRACE("(%p)->(%08x %p %p)\n", This, cmdexecopt, in, out);

    if(!in)
        return S_OK;

    if(V_VT(in) == VT_BOOL)
        set_dirty(This, V_BOOL(in));
    else
        FIXME("unsupported arg %s\n", debugstr_variant(in));

    return S_OK;
}