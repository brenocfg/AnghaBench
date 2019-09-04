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

int hex2int(int ch)
{
    if (ch >= 'a' && ch <= 'f') return ch + 10 - 'a';
    else if (ch >= 'A' && ch <= 'F') return ch + 10 - 'A';
    else return ch - '0';
}