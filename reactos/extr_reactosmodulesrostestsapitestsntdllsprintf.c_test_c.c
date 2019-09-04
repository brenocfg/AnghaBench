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
test_c()
{
    char buffer[64];

    sprintf(buffer, "%c", 0x3031);
    ok_str(buffer, "1");

    sprintf(buffer, "%hc", 0x3031);
    ok_str(buffer, "1");

    sprintf(buffer, "%wc", 0x3031);
    ok_str(buffer, "?");

    sprintf(buffer, "%lc", 0x3031);
    ok_str(buffer, "?");

    sprintf(buffer, "%Lc", 0x3031);
    ok_str(buffer, "1");

    sprintf(buffer, "%Ic", 0x3031);
    ok_str(buffer, "Ic");

    sprintf(buffer, "%Iwc", 0x3031);
    ok_str(buffer, "Iwc");

    sprintf(buffer, "%I32c", 0x3031);
    ok_str(buffer, "1");

    sprintf(buffer, "%I64c", 0x3031);
    ok_str(buffer, "1");

    sprintf(buffer, "%4c", 0x3031);
    ok_str(buffer, "   1");

    sprintf(buffer, "%04c", 0x3031);
    ok_str(buffer, "0001");

    sprintf(buffer, "%+4c", 0x3031);
    ok_str(buffer, "   1");

}