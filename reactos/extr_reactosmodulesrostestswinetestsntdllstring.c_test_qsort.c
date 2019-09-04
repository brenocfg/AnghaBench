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

/* Variables and functions */
 int /*<<< orphan*/  charcomparefunc ; 
 int /*<<< orphan*/  intcomparefunc ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  p_qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcomparefunc ; 

__attribute__((used)) static void test_qsort(void)
{
    int arr[5] = { 23, 42, 8, 4, 16 };
    char carr[5] = { 42, 23, 4, 8, 16 };
    const char *strarr[7] = {
	"Hello",
	"Wine",
	"World",
	"!",
	"Hopefully",
	"Sorted",
	"."
    };

    p_qsort ((void*)arr, 0, sizeof(int), intcomparefunc);
    ok(arr[0] == 23, "badly sorted, nmemb=0, arr[0] is %d\n", arr[0]);
    ok(arr[1] == 42, "badly sorted, nmemb=0, arr[1] is %d\n", arr[1]);
    ok(arr[2] == 8,  "badly sorted, nmemb=0, arr[2] is %d\n", arr[2]);
    ok(arr[3] == 4,  "badly sorted, nmemb=0, arr[3] is %d\n", arr[3]);
    ok(arr[4] == 16, "badly sorted, nmemb=0, arr[4] is %d\n", arr[4]);

    p_qsort ((void*)arr, 1, sizeof(int), intcomparefunc);
    ok(arr[0] == 23, "badly sorted, nmemb=1, arr[0] is %d\n", arr[0]);
    ok(arr[1] == 42, "badly sorted, nmemb=1, arr[1] is %d\n", arr[1]);
    ok(arr[2] == 8,  "badly sorted, nmemb=1, arr[2] is %d\n", arr[2]);
    ok(arr[3] == 4,  "badly sorted, nmemb=1, arr[3] is %d\n", arr[3]);
    ok(arr[4] == 16, "badly sorted, nmemb=1, arr[4] is %d\n", arr[4]);

    p_qsort ((void*)arr, 5, 0, intcomparefunc);
    ok(arr[0] == 23, "badly sorted, size=0, arr[0] is %d\n", arr[0]);
    ok(arr[1] == 42, "badly sorted, size=0, arr[1] is %d\n", arr[1]);
    ok(arr[2] == 8,  "badly sorted, size=0, arr[2] is %d\n", arr[2]);
    ok(arr[3] == 4,  "badly sorted, size=0, arr[3] is %d\n", arr[3]);
    ok(arr[4] == 16, "badly sorted, size=0, arr[4] is %d\n", arr[4]);

    p_qsort ((void*)arr, 5, sizeof(int), intcomparefunc);
    ok(arr[0] == 4,  "badly sorted, arr[0] is %d\n", arr[0]);
    ok(arr[1] == 8,  "badly sorted, arr[1] is %d\n", arr[1]);
    ok(arr[2] == 16, "badly sorted, arr[2] is %d\n", arr[2]);
    ok(arr[3] == 23, "badly sorted, arr[3] is %d\n", arr[3]);
    ok(arr[4] == 42, "badly sorted, arr[4] is %d\n", arr[4]);

    p_qsort ((void*)carr, 5, sizeof(char), charcomparefunc);
    ok(carr[0] == 4,  "badly sorted, carr[0] is %d\n", carr[0]);
    ok(carr[1] == 8,  "badly sorted, carr[1] is %d\n", carr[1]);
    ok(carr[2] == 16, "badly sorted, carr[2] is %d\n", carr[2]);
    ok(carr[3] == 23, "badly sorted, carr[3] is %d\n", carr[3]);
    ok(carr[4] == 42, "badly sorted, carr[4] is %d\n", carr[4]);

    p_qsort ((void*)strarr, 7, sizeof(char*), strcomparefunc);
    ok(!strcmp(strarr[0],"!"),  "badly sorted, strarr[0] is %s\n", strarr[0]);
    ok(!strcmp(strarr[1],"."),  "badly sorted, strarr[1] is %s\n", strarr[1]);
    ok(!strcmp(strarr[2],"Hello"),  "badly sorted, strarr[2] is %s\n", strarr[2]);
    ok(!strcmp(strarr[3],"Hopefully"),  "badly sorted, strarr[3] is %s\n", strarr[3]);
    ok(!strcmp(strarr[4],"Sorted"),  "badly sorted, strarr[4] is %s\n", strarr[4]);
    ok(!strcmp(strarr[5],"Wine"),  "badly sorted, strarr[5] is %s\n", strarr[5]);
    ok(!strcmp(strarr[6],"World"),  "badly sorted, strarr[6] is %s\n", strarr[6]);
}