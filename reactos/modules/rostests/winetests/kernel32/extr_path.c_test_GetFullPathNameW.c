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
typedef  int /*<<< orphan*/  invalid_parameters ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_INVALID_NAME ; 
 int GetFullPathNameW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_GetFullPathNameW(void)
{
    static const WCHAR emptyW[] = {0};
    static const WCHAR deadbeefW[] = {'d','e','a','d','b','e','e','f',0};

    WCHAR output[MAX_PATH], *filepart;
    DWORD ret;
    int i;

    const struct
    {
        LPCWSTR name;
        DWORD len;
        LPWSTR buffer;
        LPWSTR *lastpart;
        int win7_expect;
    } invalid_parameters[] =
    {
        {NULL,   0,        NULL,   NULL},
        {NULL,   0,        NULL,   &filepart, 1},
        {NULL,   MAX_PATH, NULL,   NULL},
        {NULL,   MAX_PATH, output, NULL},
        {NULL,   MAX_PATH, output, &filepart, 1},
        {emptyW, 0,        NULL,   NULL},
        {emptyW, 0,        NULL,   &filepart, 1},
        {emptyW, MAX_PATH, NULL,   NULL},
        {emptyW, MAX_PATH, output, NULL},
        {emptyW, MAX_PATH, output, &filepart, 1},
    };

    SetLastError(0xdeadbeef);
    ret = GetFullPathNameW(NULL, 0, NULL, NULL);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetFullPathNameW is not available\n");
        return;
    }

    for (i = 0; i < sizeof(invalid_parameters)/sizeof(invalid_parameters[0]); i++)
    {
        SetLastError(0xdeadbeef);
        lstrcpyW(output, deadbeefW);
        filepart = (WCHAR *)0xdeadbeef;
        ret = GetFullPathNameW(invalid_parameters[i].name,
                               invalid_parameters[i].len,
                               invalid_parameters[i].buffer,
                               invalid_parameters[i].lastpart);
        ok(!ret, "[%d] Expected GetFullPathNameW to return 0, got %u\n", i, ret);
        ok(!lstrcmpW(output, deadbeefW), "[%d] Expected the output buffer to be unchanged, got %s\n", i, wine_dbgstr_w(output));
        ok(filepart == (WCHAR *)0xdeadbeef ||
           (invalid_parameters[i].win7_expect && filepart == NULL),
           "[%d] Expected output file part pointer to be untouched, got %p\n", i, filepart);
        ok(GetLastError() == 0xdeadbeef ||
           GetLastError() == ERROR_INVALID_NAME, /* Win7 */
           "[%d] Expected GetLastError() to return 0xdeadbeef, got %u\n",
           i, GetLastError());
    }
}