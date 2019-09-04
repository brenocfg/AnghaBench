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

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*) ; 
 char const* p_wcsrchr (char const*,char) ; 

__attribute__((used)) static void test_wcsrchr(void)
{
    static const WCHAR teststringW[] = {'a','b','r','a','c','a','d','a','b','r','a',0};

    ok(p_wcsrchr(teststringW, 'a') == teststringW + 10,
       "wcsrchr should have returned a pointer to the last 'a' character\n");
    ok(p_wcsrchr(teststringW, 0) == teststringW + 11,
       "wcsrchr should have returned a pointer to the null terminator\n");
    ok(p_wcsrchr(teststringW, 'x') == NULL,
       "wcsrchr should have returned NULL\n");
}