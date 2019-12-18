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
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
test_s()
{
    char buffer[64];

    sprintf(buffer, "%s", "test");
    ok_str(buffer, "test");

    sprintf(buffer, "%S", L"test");
    ok_str(buffer, "test");

    sprintf(buffer, "%ls", L"test");
    ok_str(buffer, "test");

    sprintf(buffer, "%ws", L"test");
    ok_str(buffer, "test");

    sprintf(buffer, "%hs", "test");
    ok_str(buffer, "test");

    sprintf(buffer, "%hS", "test");
    ok_str(buffer, "test");

    sprintf(buffer, "%7s", "test");
    ok_str(buffer, "   test");

    sprintf(buffer, "%07s", "test");
    ok_str(buffer, "000test");

    sprintf(buffer, "%.3s", "test");
    ok_str(buffer, "tes");

    sprintf(buffer, "%+7.3s", "test");
    ok_str(buffer, "    tes");

    sprintf(buffer, "%+4.0s", "test");
    ok_str(buffer, "    ");


}