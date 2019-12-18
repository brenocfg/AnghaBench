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
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pUrlIsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pUrlIsW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_UrlIs_null(DWORD flag)
{
    BOOL ret;
    ret = pUrlIsA(NULL, flag);
    ok(ret == FALSE, "pUrlIsA(NULL, %d) failed\n", flag);
    ret = pUrlIsW(NULL, flag);
    ok(ret == FALSE, "pUrlIsW(NULL, %d) failed\n", flag);
}