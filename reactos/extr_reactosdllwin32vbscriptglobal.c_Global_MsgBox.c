#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* desc; } ;
typedef  TYPE_2__ vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int MB_OK ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  show_msgbox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Global_MsgBox(vbdisp_t *This, VARIANT *args, unsigned args_cnt, VARIANT *res)
{
    BSTR prompt, title = NULL;
    int type = MB_OK;
    HRESULT hres;

    TRACE("\n");

    assert(1 <= args_cnt && args_cnt <= 5);

    hres = to_string(args, &prompt);
    if(FAILED(hres))
        return hres;

    if(args_cnt > 1)
        hres = to_int(args+1, &type);

    if(SUCCEEDED(hres) && args_cnt > 2)
        hres = to_string(args+2, &title);

    if(SUCCEEDED(hres) && args_cnt > 3) {
        FIXME("unsupported arg_cnt %d\n", args_cnt);
        hres = E_NOTIMPL;
    }

    if(SUCCEEDED(hres))
        hres = show_msgbox(This->desc->ctx, prompt, type, title, res);

    SysFreeString(prompt);
    SysFreeString(title);
    return hres;
}