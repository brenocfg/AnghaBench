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
typedef  int /*<<< orphan*/  arr ;

/* Variables and functions */
 int /*<<< orphan*/  intcomparefunc ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int* p_bsearch (int*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_bsearch(void)
{
    int arr[7] = { 1, 3, 4, 8, 16, 23, 42 };
    int *x, l, i, j;

    /* just try all array sizes */
    for (j=1;j<sizeof(arr)/sizeof(arr[0]);j++) {
        for (i=0;i<j;i++) {
            l = arr[i];
            x = p_bsearch (&l, arr, j, sizeof(arr[0]), intcomparefunc);
            ok (x == &arr[i], "bsearch did not find %d entry in loopsize %d.\n", i, j);
        }
        l = 4242;
        x = p_bsearch (&l, arr, j, sizeof(arr[0]), intcomparefunc);
        ok (x == NULL, "bsearch did find 4242 entry in loopsize %d.\n", j);
    }
}