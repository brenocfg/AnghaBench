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
struct DbgHelpStringTab {char const*** Table; } ;

/* Variables and functions */

const char*
DbgHelpGetString(struct DbgHelpStringTab *tab, int id)
{
    int i = id >> 10;
    int bucket = id & 0x3ff;
    return tab->Table[bucket][i];
}