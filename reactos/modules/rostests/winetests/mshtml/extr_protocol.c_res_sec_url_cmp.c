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
typedef  int /*<<< orphan*/  fileW ;
typedef  int /*<<< orphan*/  buf ;
typedef  float WCHAR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int SearchPathW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__,float*) ; 
 scalar_t__ memcmp (scalar_t__,float const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ wine_dbgstr_w (scalar_t__) ; 

__attribute__((used)) static void res_sec_url_cmp(LPCWSTR url, DWORD size, LPCWSTR file)
{
    WCHAR buf[MAX_PATH];
    DWORD len;

    static const WCHAR fileW[] = {'f','i','l','e',':','/','/'};

    if(size < sizeof(fileW)/sizeof(WCHAR) || memcmp(url, fileW, sizeof(fileW))) {
        ok(0, "wrong URL protocol\n");
        return;
    }

    SetLastError(0xdeadbeef);
    len = SearchPathW(NULL, file, NULL, sizeof(buf)/sizeof(WCHAR), buf, NULL);
    if(!len) {
        if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
            win_skip("SearchPathW is not implemented\n");
        else
            ok(0, "SearchPath failed: %u\n", GetLastError());
        return;
    }

    len += sizeof(fileW)/sizeof(WCHAR)+1;
    ok(len == size, "wrong size %u, expected %u\n", size, len);
    ok(!lstrcmpW(url + sizeof(fileW)/sizeof(WCHAR), buf), "wrong file part %s\n", wine_dbgstr_w(url));
}