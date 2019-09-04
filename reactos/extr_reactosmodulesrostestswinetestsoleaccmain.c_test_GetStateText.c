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
typedef  int WCHAR ;
typedef  int UINT ;
typedef  char CHAR ;

/* Variables and functions */
 int GetStateTextA (unsigned int,char*,int) ; 
 int GetStateTextW (int,int*,int) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_wn (void*,int) ; 

__attribute__((used)) static void test_GetStateText(void)
{
    WCHAR buf[1024], buf2[1024];
    char bufa[1024];
    void *ptr;
    UINT ret, ret2;
    int i;

    ret2 = GetStateTextW(0, NULL, 1024);
    ok(ret2, "GetStateText failed\n");

    ptr = NULL;
    ret = GetStateTextW(0, (WCHAR*)&ptr, 0);
    ok(ret == ret2, "got %d, expected %d\n", ret, ret2);
    ok(ptr != NULL, "ptr was not changed\n");

    ret = GetStateTextW(0, buf, 1024);
    ok(ret == ret2, "got %d, expected %d\n", ret, ret2);
    ok(!memcmp(buf, ptr, ret*sizeof(WCHAR)), "got %s, expected %s\n",
            wine_dbgstr_wn(buf, ret), wine_dbgstr_wn(ptr, ret));

    ret = GetStateTextW(0, buf, 1);
    ok(!ret, "got %d, expected 0\n", ret);
    ok(!buf[0], "buf[0] = '%c'\n", buf[0]);

    for(i=0; i<31; i++) {
        ret = GetStateTextW(1<<i, buf, 1024);
        ok(ret, "%d) GetStateText failed\n", i);
    }
    ret = GetStateTextW(1u<<31, buf, 1024);
    ok(!ret, "31) GetStateText succeeded: %d\n", ret);

    ret = GetStateTextW(2, buf, 1024);
    ok(ret, "GetStateText failed\n");
    ret2 = GetStateTextW(3, buf2, 1024);
    ok(ret2, "GetStateText failed\n");
    ok(ret == ret2, "got %d, expected %d\n", ret2, ret);
    ok(!memcmp(buf, buf2, ret*sizeof(WCHAR)),
            "GetStateText(2,...) returned different data than GetStateText(3,...)\n");

    ret2 = GetStateTextA(0, NULL, 1024);
    ok(ret2, "GetStateText failed\n");

    ptr = NULL;
    ret = GetStateTextA(0, (CHAR*)&ptr, 0);
    ok(!ret, "got %d\n", ret);
    ok(ptr == NULL, "ptr was changed\n");

    ret = GetStateTextA(0, NULL, 0);
    ok(ret == ret2, "got %d, expected %d\n", ret, ret2);

    ret = GetStateTextA(0, bufa, 1024);
    ok(ret == ret2, "got %d, expected %d\n", ret, ret2);

    ret = GetStateTextA(0, bufa, 1);
    ok(!ret, "got %d, expected 0\n", ret);
    ok(!bufa[0], "bufa[0] = '%c'\n", bufa[0]);

    for(i=0; i<31; i++) {
        ret = GetStateTextA(1<<i, bufa, 1024);
        ok(ret, "%d) GetStateText failed\n", i);
    }
    ret = GetStateTextA(1u<<31, bufa, 1024);
    ok(!ret, "31) GetStateText succeeded: %d\n", ret);
}