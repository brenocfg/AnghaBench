#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_7__ {int uiCodePage; int /*<<< orphan*/  wszProportionalFont; int /*<<< orphan*/  wszFixedWidthFont; int /*<<< orphan*/  wszDescription; int /*<<< orphan*/  ScriptId; } ;
typedef  TYPE_1__ SCRIPTINFO ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  IEnumScript ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_FAIL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int IEnumScript_Next (int /*<<< orphan*/ *,int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  IEnumScript_Release (int /*<<< orphan*/ *) ; 
 int IEnumScript_Reset (int /*<<< orphan*/ *) ; 
 int IEnumScript_Skip (int /*<<< orphan*/ *,int) ; 
 int IMultiLanguage2_EnumScripts (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IMultiLanguage2_GetNumberOfScripts (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ pGetCPInfoExA ; 
 int /*<<< orphan*/  scriptinfo_cmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_EnumScripts(IMultiLanguage2 *iML2, DWORD flags)
{
    IEnumScript *iEnumScript = NULL;
    SCRIPTINFO *sinfo;
    SCRIPTINFO sinfo2;
    HRESULT ret;
    ULONG i, n;
    UINT total;

    total = 0;
    ret = IMultiLanguage2_GetNumberOfScripts(iML2, &total);
    ok(ret == S_OK && total != 0, "IMultiLanguage2_GetNumberOfScripts: expected S_OK/!0, got %08x/%u\n", ret, total);

    trace("total mlang supported scripts %u\n", total);

    ret = IMultiLanguage2_EnumScripts(iML2, flags, LANG_NEUTRAL, &iEnumScript);
    ok(ret == S_OK && iEnumScript, "IMultiLanguage2_EnumScripts: expected S_OK/!NULL, got %08x/%p\n", ret, iEnumScript);

    ret = IEnumScript_Reset(iEnumScript);
    ok(ret == S_OK, "IEnumScript_Reset: expected S_OK, got %08x\n", ret);
    n = 65536;
    ret = IEnumScript_Next(iEnumScript, 0, NULL, &n);
    ok(n == 65536 && ret == E_FAIL, "IEnumScript_Next: expected 65536/E_FAIL, got %u/%08x\n", n, ret);
    ret = IEnumScript_Next(iEnumScript, 0, NULL, NULL);
    ok(ret == E_FAIL, "IEnumScript_Next: expected E_FAIL, got %08x\n", ret);

    sinfo = HeapAlloc(GetProcessHeap(), 0, sizeof(*sinfo) * total * 2);

    n = total * 2;
    ret = IEnumScript_Next(iEnumScript, 0, sinfo, &n);
    ok(ret == S_FALSE && n == 0, "IEnumScript_Next: expected S_FALSE/0, got %08x/%u\n", ret, n);

    n = total * 2;
    ret = IEnumScript_Next(iEnumScript, n, sinfo, &n);
    ok(ret == S_OK && n != 0, "IEnumScript_Next: expected S_OK, got %08x/%u\n", ret, n);

    trace("flags %08x, enumerated scripts %u\n", flags, n);

    if (!flags)
    {
	ok(n == total, "IEnumScript_Next: expected %u, got %u\n", total, n);
    }

    total = n;

    for (i = 0; pGetCPInfoExA && i < n; i++)
    {
#ifdef DUMP_SCRIPT_INFO
	trace("SCRIPTINFO #%u:\n"
	      "ScriptId %08x\n"
	      "uiCodePage %u\n"
	      "wszDescription %s\n"
	      "wszFixedWidthFont %s\n"
	      "wszProportionalFont %s\n\n",
	      i,
	      sinfo[i].ScriptId,
	      sinfo[i].uiCodePage,
	      wine_dbgstr_w(sinfo[i].wszDescription),
	      wine_dbgstr_w(sinfo[i].wszFixedWidthFont),
	      wine_dbgstr_w(sinfo[i].wszProportionalFont));
        trace("%u codepage %u\n", i, sinfo[i].uiCodePage);
#endif
    }

    /* now IEnumScript_Next should fail, since pointer is at the end */
    n = 1;
    ret = IEnumScript_Next(iEnumScript, 1, &sinfo2, &n);
    ok(ret == S_FALSE && n == 0, "IEnumScript_Next: expected S_FALSE/0, got %08x/%u\n", ret, n);

    ret = IEnumScript_Reset(iEnumScript);
    ok(ret == S_OK, "IEnumScript_Reset: expected S_OK, got %08x\n", ret);
    n = 0;
    ret = IEnumScript_Next(iEnumScript, 1, &sinfo2, &n);
    ok(n == 1 && ret == S_OK, "IEnumScript_Next: expected 1/S_OK, got %u/%08x\n", n, ret);
    scriptinfo_cmp(sinfo, &sinfo2);

    if (0)
    {
    /* Due to a bug in MS' implementation of IEnumScript_Skip
     * it's not used here.
     */
    ret = IEnumScript_Skip(iEnumScript, 1);
    ok(ret == S_OK, "IEnumScript_Skip: expected S_OK, got %08x\n", ret);
    }
    for (i = 0; i < total - 1; i++)
    {
        n = 0;
        ret = IEnumScript_Next(iEnumScript, 1, &sinfo2, &n);
        ok(n == 1 && ret == S_OK, "IEnumScript_Next: expected 1/S_OK, got %u/%08x\n", n, ret);
        scriptinfo_cmp(&sinfo[i + 1], &sinfo2);
    }

    HeapFree(GetProcessHeap(), 0, sinfo);
    IEnumScript_Release(iEnumScript);
}