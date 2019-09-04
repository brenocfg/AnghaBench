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
typedef  char WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HlinkParseDisplayName (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_IsSystemMoniker (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ MKSYS_CLASSMONIKER ; 
 scalar_t__ MKSYS_FILEMONIKER ; 
 scalar_t__ MKSYS_URLMONIKER ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* winehq_urlW ; 

__attribute__((used)) static void test_HlinkParseDisplayName(void)
{
    IMoniker *mon = NULL;
    LPWSTR name;
    DWORD issys;
    ULONG eaten = 0;
    IBindCtx *bctx;
    HRESULT hres;

    static const WCHAR invalid_urlW[] = {'t','e','s','t',':','1','2','3','a','b','c',0};
    static const WCHAR clsid_nameW[] = {'c','l','s','i','d',':',
            '2','0','D','0','4','F','E','0','-','3','A','E','A','-','1','0','6','9','-','A','2','D','8',
            '-','0','8','0','0','2','B','3','0','3','0','9','D',':',0};
    static const WCHAR file_urlW[] =
            {'f','i','l','e',':','/','/','/','c',':','\\','f','i','l','e','.','t','x','t',0};

    CreateBindCtx(0, &bctx);

    hres = HlinkParseDisplayName(bctx, winehq_urlW, FALSE, &eaten, &mon);
    ok(hres == S_OK, "HlinkParseDisplayName failed: %08x\n", hres);
    ok(eaten == ARRAY_SIZE(winehq_urlW)-1, "eaten=%d\n", eaten);
    ok(mon != NULL, "mon == NULL\n");

    hres = IMoniker_GetDisplayName(mon, bctx, 0, &name);
    ok(hres == S_OK, "GetDisplayName failed: %08x\n", hres);
    ok(!lstrcmpW(name, winehq_urlW), "wrong display name %s\n", wine_dbgstr_w(name));
    CoTaskMemFree(name);

    hres = IMoniker_IsSystemMoniker(mon, &issys);
    ok(hres == S_OK, "IsSystemMoniker failed: %08x\n", hres);
    ok(issys == MKSYS_URLMONIKER, "issys=%x\n", issys);

    IMoniker_Release(mon);

    hres = HlinkParseDisplayName(bctx, clsid_nameW, FALSE, &eaten, &mon);
    ok(hres == S_OK, "HlinkParseDisplayName failed: %08x\n", hres);
    ok(eaten == ARRAY_SIZE(clsid_nameW)-1, "eaten=%d\n", eaten);
    ok(mon != NULL, "mon == NULL\n");

    hres = IMoniker_IsSystemMoniker(mon, &issys);
    ok(hres == S_OK, "IsSystemMoniker failed: %08x\n", hres);
    ok(issys == MKSYS_CLASSMONIKER, "issys=%x\n", issys);

    IMoniker_Release(mon);

    hres = HlinkParseDisplayName(bctx, invalid_urlW, FALSE, &eaten, &mon);
    ok(hres == S_OK, "HlinkParseDisplayName failed: %08x\n", hres);
    ok(eaten == ARRAY_SIZE(invalid_urlW)-1, "eaten=%d\n", eaten);
    ok(mon != NULL, "mon == NULL\n");

    hres = IMoniker_GetDisplayName(mon, bctx, 0, &name);
    ok(hres == S_OK, "GetDisplayName failed: %08x\n", hres);
    ok(!lstrcmpW(name, invalid_urlW), "wrong display name %s\n", wine_dbgstr_w(name));
    CoTaskMemFree(name);

    hres = IMoniker_IsSystemMoniker(mon, &issys);
    ok(hres == S_OK, "IsSystemMoniker failed: %08x\n", hres);
    ok(issys == MKSYS_FILEMONIKER, "issys=%x\n", issys);

    IMoniker_Release(mon);

    hres = HlinkParseDisplayName(bctx, file_urlW, FALSE, &eaten, &mon);
    ok(hres == S_OK, "HlinkParseDisplayName failed: %08x\n", hres);
    ok(eaten == ARRAY_SIZE(file_urlW)-1, "eaten=%d\n", eaten);
    ok(mon != NULL, "mon == NULL\n");

    hres = IMoniker_GetDisplayName(mon, bctx, 0, &name);
    ok(hres == S_OK, "GetDisplayName failed: %08x\n", hres);
    ok(!lstrcmpW(name, file_urlW+8), "wrong display name %s\n", wine_dbgstr_w(name));
    CoTaskMemFree(name);

    hres = IMoniker_IsSystemMoniker(mon, &issys);
    ok(hres == S_OK, "IsSystemMoniker failed: %08x\n", hres);
    ok(issys == MKSYS_FILEMONIKER, "issys=%x\n", issys);

    IMoniker_Release(mon);
    IBindCtx_Release(bctx);
}