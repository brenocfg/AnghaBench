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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LONG_PTR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAutoComplete ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ACLMulti ; 
 int /*<<< orphan*/  CLSID_AutoComplete ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 scalar_t__ GetWindowLongPtrA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IAutoComplete_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAutoComplete_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IACList ; 
 int /*<<< orphan*/  IID_IAutoComplete ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  hEdit ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static IAutoComplete *test_init(void)
{
    HRESULT r;
    IAutoComplete *ac, *ac2;
    IUnknown *acSource;
    LONG_PTR user_data;

    /* AutoComplete instance */
    r = CoCreateInstance(&CLSID_AutoComplete, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IAutoComplete, (LPVOID*)&ac);
    if (r == REGDB_E_CLASSNOTREG)
    {
        win_skip("CLSID_AutoComplete is not registered\n");
        return NULL;
    }
    ok(r == S_OK, "no IID_IAutoComplete (0x%08x)\n", r);

    /* AutoComplete source */
    r = CoCreateInstance(&CLSID_ACLMulti, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IACList, (LPVOID*)&acSource);
    if (r == REGDB_E_CLASSNOTREG)
    {
        win_skip("CLSID_ACLMulti is not registered\n");
        IAutoComplete_Release(ac);
        return NULL;
    }
    ok(r == S_OK, "no IID_IACList (0x%08x)\n", r);

    user_data = GetWindowLongPtrA(hEdit, GWLP_USERDATA);
    ok(user_data == 0, "Expected the edit control user data to be zero\n");

    /* bind to edit control */
    r = IAutoComplete_Init(ac, hEdit, acSource, NULL, NULL);
    ok(r == S_OK, "Init returned 0x%08x\n", r);

    user_data = GetWindowLongPtrA(hEdit, GWLP_USERDATA);
    ok(user_data == 0, "Expected the edit control user data to be zero\n");

    /* bind a different object to the same edit control */
    r = CoCreateInstance(&CLSID_AutoComplete, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IAutoComplete, (LPVOID*)&ac2);
    ok(r == S_OK, "no IID_IAutoComplete (0x%08x)\n", r);

    r = IAutoComplete_Init(ac2, hEdit, acSource, NULL, NULL);
    ok(r == S_OK, "Init returned 0x%08x\n", r);
    IAutoComplete_Release(ac2);

    IUnknown_Release(acSource);

    return ac;
}