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
typedef  int /*<<< orphan*/  buf ;
typedef  int DWORD ;

/* Variables and functions */
 int GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 scalar_t__ broken (int) ; 
 scalar_t__ lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_GetTempPathA(char* tmp_dir)
{
    DWORD len, slen, len_with_null;
    char buf[MAX_PATH];

    len_with_null = strlen(tmp_dir) + 1;

    lstrcpyA(buf, "foo");
    len = GetTempPathA(MAX_PATH, buf);
    ok(len <= MAX_PATH, "should fit into MAX_PATH\n");
    ok(lstrcmpiA(buf, tmp_dir) == 0, "expected [%s], got [%s]\n",tmp_dir,buf);
    ok(len == strlen(buf), "returned length should be equal to the length of string\n");

    /* Some versions of Windows touch the buffer, some don't so we don't
     * test that. Also, NT sometimes exaggerates the required buffer size
     * so we cannot test for an exact match. Finally, the
     * 'len_with_null - 1' case is so buggy on Windows it's not testable.
     * For instance in some cases Win98 returns len_with_null - 1 instead
     * of len_with_null.
     */
    len = GetTempPathA(1, buf);
    ok(len >= len_with_null, "Expected >= %u, got %u\n", len_with_null, len);

    len = GetTempPathA(0, NULL);
    ok(len >= len_with_null, "Expected >= %u, got %u\n", len_with_null, len);

    /* The call above gave us the buffer size that Windows thinks is needed
     * so the next call should work
     */
    lstrcpyA(buf, "foo");
    len = GetTempPathA(len, buf);
    ok(lstrcmpiA(buf, tmp_dir) == 0, "expected [%s], got [%s]\n",tmp_dir,buf);
    ok(len == strlen(buf), "returned length should be equal to the length of string\n");

    memset(buf, 'a', sizeof(buf));
    len = GetTempPathA(sizeof(buf), buf);
    ok(lstrcmpiA(buf, tmp_dir) == 0, "expected [%s], got [%s]\n",tmp_dir,buf);
    ok(len == strlen(buf), "returned length should be equal to the length of string\n");
    /* The rest of the buffer remains untouched */
    slen = len + 1;
    for(len++; len < sizeof(buf); len++)
        ok(buf[len] == 'a', "expected 'a' at [%d], got 0x%x\n", len, buf[len]);

    /* When the buffer is not long enough it remains untouched */
    memset(buf, 'a', sizeof(buf));
    len = GetTempPathA(slen / 2, buf);
    ok(len == slen || broken(len == slen + 1) /* read the big comment above */ ,
       "expected %d, got %d\n", slen, len);
    for(len = 0; len < sizeof(buf) / sizeof(buf[0]); len++)
        ok(buf[len] == 'a', "expected 'a' at [%d], got 0x%x\n", len, buf[len]);
}