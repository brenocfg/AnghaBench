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
 int /*<<< orphan*/  ExitProcess (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void test__popen_child(void)
{
    /* don't execute any tests here */
    /* ExitProcess is used to set return code of _pclose */
    printf("child output\n");
    ExitProcess(0x37);
}