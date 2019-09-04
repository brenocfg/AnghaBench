#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_6__ {unsigned char* pbData; scalar_t__ cbData; } ;
typedef  TYPE_1__ DATA_BLOB ;

/* Variables and functions */
 char const* GetLastError () ; 
 int /*<<< orphan*/  LocalFree (unsigned char*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrlenA (char const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCryptProtectData (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int pCryptUnprotectData (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_simpleroundtrip(const char *plaintext)
{
    DATA_BLOB input;
    DATA_BLOB encrypted;
    DATA_BLOB output;
    int res;
    WCHAR emptyW[1];

    emptyW[0] = 0;
    input.pbData = (unsigned char *)plaintext;
    input.cbData = strlen(plaintext);
    res = pCryptProtectData(&input, emptyW, NULL, NULL, NULL, 0, &encrypted);
    ok(res != 0 || broken(!res), "can't protect\n");
    if (!res)
    {
        /* Fails on Win9x, NT4 */
        win_skip("CryptProtectData failed\n");
        return;
    }

    res = pCryptUnprotectData(&encrypted, NULL, NULL, NULL, NULL, 0, &output);
    ok(res != 0, "can't unprotect; last error %u\n", GetLastError());
    ok(output.cbData == strlen(plaintext), "output wrong length %d for input '%s', wanted %d\n", output.cbData, plaintext, lstrlenA(plaintext));
    ok(!memcmp(plaintext, (char *)output.pbData, output.cbData), "output wrong contents for input '%s'\n", plaintext);
    LocalFree(output.pbData);
    LocalFree(encrypted.pbData);
}