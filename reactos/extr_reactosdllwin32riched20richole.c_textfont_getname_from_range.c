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
struct TYPE_3__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ textfont_prop_val ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  IRichEditOleImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_RELEASED ; 
 int /*<<< orphan*/  FONT_NAME ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_range_reole (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_textfont_prop_for_pos (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static HRESULT textfont_getname_from_range(ITextRange *range, BSTR *ret)
{
    const IRichEditOleImpl *reole;
    textfont_prop_val v;
    HRESULT hr;
    LONG start;

    if (!(reole = get_range_reole(range)))
        return CO_E_RELEASED;

    ITextRange_GetStart(range, &start);
    hr = get_textfont_prop_for_pos(reole, start, FONT_NAME, &v);
    *ret = v.str;
    return hr;
}