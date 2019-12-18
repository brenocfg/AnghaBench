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
typedef  int /*<<< orphan*/  pCC ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  COMMCONFIG ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_BADKEY ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * com1A ; 
 int /*<<< orphan*/ * emptyA ; 
 char* fmt_comA ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 scalar_t__ pGetDefaultCommConfigA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  str_colonA ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_drvGetDefaultCommConfigA(void)
{
    COMMCONFIG  pCC[3];
    CHAR        bufferA[16];
    DWORD       i;
    DWORD       res;
    DWORD       len;


    /* off by one: one byte smaller */
    i   = sizeof(COMMCONFIG);
    len = sizeof(COMMCONFIG) -1;
    ZeroMemory(pCC, sizeof(pCC));
    SetLastError(0xdeadbeef);
    res = pGetDefaultCommConfigA(com1A, pCC, &len);
    if (res == ERROR_CALL_NOT_IMPLEMENTED) {
        /* NT does not implement the ANSI API */
        win_skip("*A not implemented\n");
        return;
    }
    ok( (res == ERROR_INSUFFICIENT_BUFFER) && (len >= i),
        "returned %u with %u and %u (expected "
        "ERROR_INSUFFICIENT_BUFFER and '>= %u')\n", res, GetLastError(), len, i);

    /* test ports "com0" - "com10" */
    for (i = 0; i < 11 ; i++) {
        sprintf(bufferA, fmt_comA, i);
        len = sizeof(pCC);
        ZeroMemory(pCC, sizeof(pCC));
        SetLastError(0xdeadbeef);
        res = pGetDefaultCommConfigA(bufferA, pCC, &len);
        if (i == 0) {
            ok( res == ERROR_BADKEY,
                "returned %u with %u and %u for %s (expected "
                "ERROR_BADKEY)\n", res, GetLastError(), len, bufferA);
        }
        else
        {
            ok((res == ERROR_SUCCESS) || (res == ERROR_BADKEY),
               "returned %u with %u and %u for %s (expected ERROR_SUCCESS or "
               "ERROR_BADKEY)\n", res, GetLastError(), len, bufferA);
        }

        /* a name with a colon is invalid */
        if (res == ERROR_SUCCESS) {
            lstrcatA(bufferA, str_colonA);
            len = sizeof(pCC);
            ZeroMemory(pCC, sizeof(pCC));
            res = pGetDefaultCommConfigA(bufferA, pCC, &len);
            ok( res == ERROR_BADKEY,
                "returned %u with %u and %u for %s (expected '0' with "
                "ERROR_BADKEY)\n", res, GetLastError(), len, bufferA);
        }
    }


    /* an empty String is not allowed */
    len = sizeof(pCC);
    ZeroMemory(pCC, sizeof(pCC));
    SetLastError(0xdeadbeef);
    res = pGetDefaultCommConfigA(emptyA, pCC, &len);
    ok( res == ERROR_BADKEY,
        "returned %u with %u and %u for %s (expected ERROR_BADKEY)\n",
        res, GetLastError(), len, emptyA);

    /* some NULL checks */
    len = sizeof(pCC);
    ZeroMemory(pCC, sizeof(pCC));
    SetLastError(0xdeadbeef);
    res = pGetDefaultCommConfigA(NULL, pCC, &len);
    ok( res == ERROR_INVALID_PARAMETER,
        "returned %u with %u and %u for NULL (expected ERROR_INVALID_PARAMETER)\n",
        res, GetLastError(), len);


    len = sizeof(pCC);
    SetLastError(0xdeadbeef);
    res = pGetDefaultCommConfigA(com1A, NULL, &len);
    ok( res == ERROR_INVALID_PARAMETER,
        "returned %u with %u and %u (expected ERROR_INVALID_PARAMETER)\n",
        res, GetLastError(), len);


    SetLastError(0xdeadbeef);
    res = pGetDefaultCommConfigA(com1A, pCC, NULL);
    ok( res == ERROR_INVALID_PARAMETER,
        "returned %u with %u (expected ERROR_INVALID_PARAMETER)\n",
        res, GetLastError());
}