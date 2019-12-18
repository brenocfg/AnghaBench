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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IAutoComplete ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ACLMulti ; 
 int /*<<< orphan*/  CLSID_AutoComplete ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int E_UNEXPECTED ; 
 int IAutoComplete_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IAutoComplete_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IACList ; 
 int /*<<< orphan*/  IID_IAutoComplete ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 int REGDB_E_CLASSNOTREG ; 
 int S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * hEdit ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  hinst ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_invalid_init(void)
{
    HRESULT hr;
    IAutoComplete *ac;
    IUnknown *acSource;
    HWND edit_control;

    /* AutoComplete instance */
    hr = CoCreateInstance(&CLSID_AutoComplete, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IAutoComplete, (void **)&ac);
    if (hr == REGDB_E_CLASSNOTREG)
    {
        win_skip("CLSID_AutoComplete is not registered\n");
        return;
    }
    ok(hr == S_OK, "no IID_IAutoComplete (0x%08x)\n", hr);

    /* AutoComplete source */
    hr = CoCreateInstance(&CLSID_ACLMulti, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IACList, (void **)&acSource);
    if (hr == REGDB_E_CLASSNOTREG)
    {
        win_skip("CLSID_ACLMulti is not registered\n");
        IAutoComplete_Release(ac);
        return;
    }
    ok(hr == S_OK, "no IID_IACList (0x%08x)\n", hr);

    edit_control = CreateWindowExA(0, "EDIT", "Some text", 0, 10, 10, 300, 300,
                       hMainWnd, NULL, hinst, NULL);
    ok(edit_control != NULL, "Can't create edit control\n");

    /* The refcount of acSource would be incremented on older Windows. */
    hr = IAutoComplete_Init(ac, NULL, acSource, NULL, NULL);
    ok(hr == E_INVALIDARG ||
       broken(hr == S_OK), /* Win2k/XP/Win2k3 */
       "Init returned 0x%08x\n", hr);
    if (hr == E_INVALIDARG)
    {
        LONG ref;

        IUnknown_AddRef(acSource);
        ref = IUnknown_Release(acSource);
        ok(ref == 1, "Expected AutoComplete source refcount to be 1, got %d\n", ref);
    }

if (0)
{
    /* Older Windows versions never check the window handle, while newer
     * versions only check for NULL. Subsequent attempts to initialize the
     * object after this call succeeds would fail, because initialization
     * state is determined by whether a non-NULL window handle is stored. */
    hr = IAutoComplete_Init(ac, (HWND)0xdeadbeef, acSource, NULL, NULL);
    ok(hr == S_OK, "Init returned 0x%08x\n", hr);

    /* Tests crash on older Windows. */
    hr = IAutoComplete_Init(ac, NULL, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Init returned 0x%08x\n", hr);

    hr = IAutoComplete_Init(ac, edit_control, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "Init returned 0x%08x\n", hr);
}

    /* bind to edit control */
    hr = IAutoComplete_Init(ac, edit_control, acSource, NULL, NULL);
    ok(hr == S_OK, "Init returned 0x%08x\n", hr);

    /* try invalid parameters after successful initialization .*/
    hr = IAutoComplete_Init(ac, NULL, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG ||
       hr == E_FAIL, /* Win2k/XP/Win2k3 */
       "Init returned 0x%08x\n", hr);

    hr = IAutoComplete_Init(ac, NULL, acSource, NULL, NULL);
    ok(hr == E_INVALIDARG ||
       hr == E_FAIL, /* Win2k/XP/Win2k3 */
       "Init returned 0x%08x\n", hr);

    hr = IAutoComplete_Init(ac, edit_control, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG ||
       hr == E_FAIL, /* Win2k/XP/Win2k3 */
       "Init returned 0x%08x\n", hr);

    /* try initializing twice on the same control */
    hr = IAutoComplete_Init(ac, edit_control, acSource, NULL, NULL);
    ok(hr == E_FAIL, "Init returned 0x%08x\n", hr);

    /* try initializing with a different control */
    hr = IAutoComplete_Init(ac, hEdit, acSource, NULL, NULL);
    ok(hr == E_FAIL, "Init returned 0x%08x\n", hr);

    DestroyWindow(edit_control);

    /* try initializing with a different control after
     * destroying the original initialization control */
    hr = IAutoComplete_Init(ac, hEdit, acSource, NULL, NULL);
    ok(hr == E_UNEXPECTED ||
       hr == E_FAIL, /* Win2k/XP/Win2k3 */
       "Init returned 0x%08x\n", hr);

    IUnknown_Release(acSource);
    IAutoComplete_Release(ac);
}