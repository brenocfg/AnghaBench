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
test_x()
{
    char buffer[64];

    sprintf(buffer, "%x", 0x1234abcd);
    ok_str(buffer, "1234abcd");

    sprintf(buffer, "%X", 0x1234abcd);
    ok_str(buffer, "1234ABCD");

    sprintf(buffer, "%#x", 0x1234abcd);
    ok_str(buffer, "0x1234abcd");

    sprintf(buffer, "%#X", 0x1234abcd);
    ok_str(buffer, "0X1234ABCD");

    /* "0x" is contained in the field length */
    sprintf(buffer, "%#012X", 0x1234abcd);
    ok_str(buffer, "0X001234ABCD");

    sprintf(buffer, "%llx", 0x1234abcd5678ULL);
    ok_str(buffer, "abcd5678");

    sprintf(buffer, "%I64x", 0x1234abcd5678ULL);
    ok_str(buffer, "1234abcd5678");

}