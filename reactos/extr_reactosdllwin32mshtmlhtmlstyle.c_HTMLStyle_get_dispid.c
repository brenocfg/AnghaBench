#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dispid; } ;
typedef  TYPE_1__ style_tbl_entry_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* lookup_style_tbl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT HTMLStyle_get_dispid(DispatchEx *dispex, BSTR name, DWORD flags, DISPID *dispid)
{
    const style_tbl_entry_t *style_entry;

    style_entry = lookup_style_tbl(name);
    if(style_entry) {
        *dispid = style_entry->dispid;
        return S_OK;
    }

    return DISP_E_UNKNOWNNAME;
}