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
typedef  int /*<<< orphan*/  textfont_prop_val ;
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
struct TYPE_3__ {int /*<<< orphan*/  range; int /*<<< orphan*/ * props; scalar_t__ get_cache_enabled; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_1__ ITextFontImpl ;
typedef  int /*<<< orphan*/  IRichEditOleImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_RELEASED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * get_range_reole (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_textfont_prop_for_pos (int /*<<< orphan*/  const*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_textfont_prop_value (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_equal_textfont_prop_value (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT get_textfont_prop(const ITextFontImpl *font, enum textfont_prop_id propid, textfont_prop_val *value)
{
    const IRichEditOleImpl *reole;
    textfont_prop_val v;
    LONG start, end, i;
    HRESULT hr;

    /* when font is not attached to any range use cached values */
    if (!font->range || font->get_cache_enabled) {
        *value = font->props[propid];
        return S_OK;
    }

    if (!(reole = get_range_reole(font->range)))
        return CO_E_RELEASED;

    init_textfont_prop_value(propid, value);

    ITextRange_GetStart(font->range, &start);
    ITextRange_GetEnd(font->range, &end);

    /* iterate trough a range to see if property value is consistent */
    hr = get_textfont_prop_for_pos(reole, start, propid, &v);
    if (FAILED(hr))
        return hr;

    for (i = start + 1; i < end; i++) {
        textfont_prop_val cur;

        hr = get_textfont_prop_for_pos(reole, i, propid, &cur);
        if (FAILED(hr))
            return hr;

        if (!is_equal_textfont_prop_value(propid, &v, &cur))
            return S_OK;
    }

    *value = v;
    return S_OK;
}