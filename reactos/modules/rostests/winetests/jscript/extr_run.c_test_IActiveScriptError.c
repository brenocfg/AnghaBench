#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {int wCode; int wReserved; int dwHelpContext; int scode; int /*<<< orphan*/ * bstrHelpFile; int /*<<< orphan*/ * bstrDescription; int /*<<< orphan*/ * bstrSource; int /*<<< orphan*/ * pfnDeferredFillIn; int /*<<< orphan*/ * pvReserved; } ;
typedef  int SCODE ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IActiveScriptError ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ EXCEPINFO ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IActiveScriptError_GetExceptionInfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IActiveScriptError_GetSourceLineText (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IActiveScriptError_GetSourcePosition (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_lang_english () ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IActiveScriptError(IActiveScriptError *error, SCODE errorcode, ULONG line, LONG pos, BSTR script_source, BSTR description, BSTR line_text)
{
    HRESULT hres;
    DWORD source_context;
    ULONG line_number;
    LONG char_position;
    BSTR linetext;
    EXCEPINFO excep;

    /* IActiveScriptError_GetSourcePosition */

    hres = IActiveScriptError_GetSourcePosition(error, NULL, NULL, NULL);
    ok(hres == S_OK, "IActiveScriptError_GetSourcePosition -- hres: expected S_OK, got 0x%08x\n", hres);

    source_context = 0xdeadbeef;
    hres = IActiveScriptError_GetSourcePosition(error, &source_context, NULL, NULL);
    ok(hres == S_OK, "IActiveScriptError_GetSourcePosition -- hres: expected S_OK, got 0x%08x\n", hres);
    ok(source_context == 0, "IActiveScriptError_GetSourcePosition -- source_context: expected 0, got 0x%08x\n", source_context);

    line_number = 0xdeadbeef;
    hres = IActiveScriptError_GetSourcePosition(error, NULL, &line_number, NULL);
    ok(hres == S_OK, "IActiveScriptError_GetSourcePosition -- hres: expected S_OK, got 0x%08x\n", hres);
    ok(line_number == line, "IActiveScriptError_GetSourcePosition -- line_number: expected %d, got %d\n", line, line_number);

    char_position = 0xdeadbeef;
    hres = IActiveScriptError_GetSourcePosition(error, NULL, NULL, &char_position);
    ok(hres == S_OK, "IActiveScriptError_GetSourcePosition -- hres: expected S_OK, got 0x%08x\n", hres);
    ok(char_position == pos, "IActiveScriptError_GetSourcePosition -- char_position: expected %d, got %d\n", pos, char_position);

    /* IActiveScriptError_GetSourceLineText */

    hres = IActiveScriptError_GetSourceLineText(error, NULL);
    ok(hres == E_POINTER, "IActiveScriptError_GetSourceLineText -- hres: expected E_POINTER, got 0x%08x\n", hres);

    linetext = NULL;
    hres = IActiveScriptError_GetSourceLineText(error, &linetext);
    if (line_text) {
        ok(hres == S_OK, "IActiveScriptError_GetSourceLineText -- hres: expected S_OK, got 0x%08x\n", hres);
        ok(linetext != NULL && !lstrcmpW(linetext, line_text),
           "IActiveScriptError_GetSourceLineText -- expected %s, got %s\n", wine_dbgstr_w(line_text), wine_dbgstr_w(linetext));
    } else {
        ok(hres == E_FAIL, "IActiveScriptError_GetSourceLineText -- hres: expected S_OK, got 0x%08x\n", hres);
        ok(linetext == NULL,
           "IActiveScriptError_GetSourceLineText -- expected NULL, got %s\n", wine_dbgstr_w(linetext));
    }
    SysFreeString(linetext);

    /* IActiveScriptError_GetExceptionInfo */

    hres = IActiveScriptError_GetExceptionInfo(error, NULL);
    ok(hres == E_POINTER, "IActiveScriptError_GetExceptionInfo -- hres: expected E_POINTER, got 0x%08x\n", hres);

    excep.wCode = 0xdead;
    excep.wReserved = 0xdead;
    excep.bstrSource = (BSTR)0xdeadbeef;
    excep.bstrDescription = (BSTR)0xdeadbeef;
    excep.bstrHelpFile = (BSTR)0xdeadbeef;
    excep.dwHelpContext = 0xdeadbeef;
    excep.pvReserved = (void *)0xdeadbeef;
    excep.pfnDeferredFillIn = (void *)0xdeadbeef;
    excep.scode = 0xdeadbeef;

    hres = IActiveScriptError_GetExceptionInfo(error, &excep);
    ok(hres == S_OK, "IActiveScriptError_GetExceptionInfo -- hres: expected S_OK, got 0x%08x\n", hres);

    ok(excep.wCode == 0, "IActiveScriptError_GetExceptionInfo -- excep.wCode: expected 0, got 0x%08x\n", excep.wCode);
    ok(excep.wReserved == 0, "IActiveScriptError_GetExceptionInfo -- excep.wReserved: expected 0, got %d\n", excep.wReserved);
    if (!is_lang_english())
        skip("Non-english UI (test with hardcoded strings)\n");
    else {
        ok(excep.bstrSource != NULL && !lstrcmpW(excep.bstrSource, script_source),
           "IActiveScriptError_GetExceptionInfo -- excep.bstrSource is not valid: expected %s, got %s\n",
           wine_dbgstr_w(script_source), wine_dbgstr_w(excep.bstrSource));
        ok(excep.bstrDescription != NULL && !lstrcmpW(excep.bstrDescription, description),
           "IActiveScriptError_GetExceptionInfo -- excep.bstrDescription is not valid: got %s\n", wine_dbgstr_w(excep.bstrDescription));
    }
    ok(excep.bstrHelpFile == NULL,
       "IActiveScriptError_GetExceptionInfo -- excep.bstrHelpFile: expected NULL, got %s\n", wine_dbgstr_w(excep.bstrHelpFile));
    ok(excep.dwHelpContext == 0, "IActiveScriptError_GetExceptionInfo -- excep.dwHelpContext: expected 0, got %d\n", excep.dwHelpContext);
    ok(excep.pvReserved == NULL, "IActiveScriptError_GetExceptionInfo -- excep.pvReserved: expected NULL, got %p\n", excep.pvReserved);
    ok(excep.pfnDeferredFillIn == NULL, "IActiveScriptError_GetExceptionInfo -- excep.pfnDeferredFillIn: expected NULL, got %p\n", excep.pfnDeferredFillIn);
    ok(excep.scode == errorcode, "IActiveScriptError_GetExceptionInfo -- excep.scode: expected 0x%08x, got 0x%08x\n", errorcode, excep.scode);

    SysFreeString(excep.bstrSource);
    SysFreeString(excep.bstrDescription);
    SysFreeString(excep.bstrHelpFile);
}