#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwMask; int dwEffects; } ;
typedef  TYPE_1__ CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 

__attribute__((used)) static void ME_DumpStyleEffect(char **p, const char *name, const CHARFORMAT2W *fmt, int mask)
{
  *p += sprintf(*p, "%-22s%s\n", name, (fmt->dwMask & mask) ? ((fmt->dwEffects & mask) ? "YES" : "no") : "N/A");
}