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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/ * HRSRC ;
typedef  char const* HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * FindResourceA (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* LoadResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTITEM_GLOBALMEMBERS ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 char const* S_OK ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_success_d ; 
 int /*<<< orphan*/  global_success_i ; 
 int /*<<< orphan*/  ok (int,char*,char const*) ; 
 char* parse_script (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strict_dispid_check ; 
 char const* test_name ; 

__attribute__((used)) static void run_from_res(const char *name)
{
    const char *data;
    DWORD size, len;
    BSTR str;
    HRSRC src;
    HRESULT hres;

    strict_dispid_check = FALSE;
    test_name = name;

    src = FindResourceA(NULL, name, (LPCSTR)40);
    ok(src != NULL, "Could not find resource %s\n", name);

    size = SizeofResource(NULL, src);
    data = LoadResource(NULL, src);

    len = MultiByteToWideChar(CP_ACP, 0, data, size, NULL, 0);
    str = SysAllocStringLen(NULL, len);
    MultiByteToWideChar(CP_ACP, 0, data, size, str, len);

    SET_EXPECT(global_success_d);
    SET_EXPECT(global_success_i);
    hres = parse_script(SCRIPTITEM_GLOBALMEMBERS, str, NULL);
    CHECK_CALLED(global_success_d);
    CHECK_CALLED(global_success_i);

    ok(hres == S_OK, "parse_script failed: %08x\n", hres);
    SysFreeString(str);
}