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
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCRIPTITEM_GLOBALMEMBERS ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_script_from_file (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strict_dispid_check ; 

__attribute__((used)) static void run_from_file(const char *filename)
{
    BSTR script_str;
    HRESULT hres;

    script_str = get_script_from_file(filename);
    if(!script_str)
        return;

    strict_dispid_check = FALSE;
    hres = parse_script(SCRIPTITEM_GLOBALMEMBERS, script_str);
    SysFreeString(script_str);
    ok(hres == S_OK, "parse_script failed: %08x\n", hres);
}