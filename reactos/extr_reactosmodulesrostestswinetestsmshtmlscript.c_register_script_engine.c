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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_TestScript ; 
 scalar_t__ CoRegisterClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  init_registry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  script_cf ; 

__attribute__((used)) static BOOL register_script_engine(void)
{
    DWORD regid;
    HRESULT hres;

    if(!init_registry(TRUE)) {
        init_registry(FALSE);
        return FALSE;
    }

    hres = CoRegisterClassObject(&CLSID_TestScript, (IUnknown *)&script_cf,
                                 CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &regid);
    ok(hres == S_OK, "Could not register script engine: %08x\n", hres);

    return TRUE;
}