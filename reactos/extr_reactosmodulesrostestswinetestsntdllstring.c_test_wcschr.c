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
 char const* p_wcschr (char const*,char) ; 

__attribute__((used)) static void test_wcschr(void)
{
    static const WCHAR teststringW[] = {'a','b','r','a','c','a','d','a','b','r','a',0};

    ok(p_wcschr(teststringW, 'a') == teststringW + 0,
       "wcschr should have returned a pointer to the first 'a' character\n");
    ok(p_wcschr(teststringW, 0) == teststringW + 11,
       "wcschr should have returned a pointer to the null terminator\n");
    ok(p_wcschr(teststringW, 'x') == NULL,
       "wcschr should have returned NULL\n");
}