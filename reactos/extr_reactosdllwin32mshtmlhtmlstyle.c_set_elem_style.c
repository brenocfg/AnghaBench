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
typedef  int /*<<< orphan*/  styleid_t ;
typedef  int /*<<< orphan*/  nsIDOMCSSStyleDeclaration ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_style_from_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMCSSStyleDeclaration_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nsstyle_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

HRESULT set_elem_style(HTMLElement *elem, styleid_t styleid, const WCHAR *val)
{
    nsIDOMCSSStyleDeclaration *style;
    HRESULT hres;

    hres = get_style_from_elem(elem, &style);
    if(FAILED(hres))
        return hres;

    hres = set_nsstyle_attr(style, styleid, val, 0);
    nsIDOMCSSStyleDeclaration_Release(style);
    return hres;
}