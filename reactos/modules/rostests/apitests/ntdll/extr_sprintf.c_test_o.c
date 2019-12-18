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
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ok_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

void
test_o()
{
    TCHAR buffer[64];

    sprintf(buffer, "%o", 1234);
    ok_str(buffer, "2322");

    sprintf(buffer, "%o", -1234);
    ok_str(buffer, "37777775456");

}