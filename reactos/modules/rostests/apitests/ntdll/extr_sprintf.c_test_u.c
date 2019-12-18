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
 int /*<<< orphan*/  ok_str (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
test_u()
{
    char buffer[64];

    sprintf(buffer, "%u", 1234);
    ok_str(buffer, "1234");

    sprintf(buffer, "%u", -1234);
    ok_str(buffer, "4294966062");

    sprintf(buffer, "%lu", -1234);
    ok_str(buffer, "4294966062");

    sprintf(buffer, "%llu", -1234);
    ok_str(buffer, "4294966062");

    sprintf(buffer, "%+u", 1234);
    ok_str(buffer, "1234");

    sprintf(buffer, "% u", 1234);
    ok_str(buffer, "1234");

}