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
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int BACKGROUND_INTENSITY ; 
 int FOREGROUND_INTENSITY ; 
 int g_attrCurrent ; 
 int g_attrPreStandout ; 
 int /*<<< orphan*/  textattr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
standout(void)
{
    g_attrPreStandout = g_attrCurrent;
    textattr((WORD) (g_attrCurrent|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY));
}