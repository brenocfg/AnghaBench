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
typedef  char LONG ;
typedef  char CHAR ;

/* Variables and functions */

LONG
HexValue(CHAR ch)
{
    if ((ch >= '0') && (ch <= '9'))
        return (ch - '0');

    if ((ch >= 'a') && (ch <= 'f'))
        return (ch - 'a' + 10);

    if ((ch >= 'A') && (ch <= 'F'))
        return (ch - 'A' + 10);

    return -1;
}