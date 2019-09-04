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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_script_af(DWORD flags, const char *src)
{
    BSTR tmp;
    HRESULT hres;

    tmp = a2bstr(src);
    hres = parse_script(flags, tmp);
    SysFreeString(tmp);
    ok(hres == S_OK, "parse_script failed: %08x\n", hres);
}