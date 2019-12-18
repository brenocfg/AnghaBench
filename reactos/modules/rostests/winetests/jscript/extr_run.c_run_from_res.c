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
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTITEM_GLOBALMEMBERS ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_success_d ; 
 int /*<<< orphan*/  global_success_i ; 
 int /*<<< orphan*/  load_res (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_from_res(const char *name)
{
    BSTR str;
    HRESULT hres;

    str = load_res(name);

    SET_EXPECT(global_success_d);
    SET_EXPECT(global_success_i);
    hres = parse_script(SCRIPTITEM_GLOBALMEMBERS, str);
    CHECK_CALLED(global_success_d);
    CHECK_CALLED(global_success_i);

    ok(hres == S_OK, "parse_script failed: %08x\n", hres);
    SysFreeString(str);
}