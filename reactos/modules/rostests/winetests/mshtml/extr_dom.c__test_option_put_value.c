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
typedef  int /*<<< orphan*/  IHTMLOptionElement ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IHTMLOptionElement_put_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _test_option_value (unsigned int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void _test_option_put_value(unsigned line, IHTMLOptionElement *option, const char *value)
{
    BSTR bstr;
    HRESULT hres;

    bstr = a2bstr(value);
    hres = IHTMLOptionElement_put_value(option, bstr);
    SysFreeString(bstr);
    ok(hres == S_OK, "put_value failed: %08x\n", hres);

    _test_option_value(line, option, value);
}