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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  SCRIPTITEM_GLOBALMEMBERS ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_script_ae(const char *src, HRESULT exhres)
{
    BSTR tmp;
    HRESULT hres;

    tmp = a2bstr(src);
    hres = parse_script(SCRIPTITEM_GLOBALMEMBERS, tmp);
    SysFreeString(tmp);
    ok(hres == exhres, "parse_script failed: %08x, expected %08x\n", hres, exhres);
}