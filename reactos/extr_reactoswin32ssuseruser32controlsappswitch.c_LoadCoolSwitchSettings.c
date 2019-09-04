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
typedef  int BOOL ;

/* Variables and functions */
 int CoolSwitch ; 
 int CoolSwitchColumns ; 
 int CoolSwitchRows ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int TRUE ; 

BOOL LoadCoolSwitchSettings(void)
{
   CoolSwitch = TRUE;
   CoolSwitchRows = 3;
   CoolSwitchColumns = 7;

   // FIXME: load the settings from registry

   TRACE("CoolSwitch: %d\n", CoolSwitch);
   TRACE("CoolSwitchRows: %d\n", CoolSwitchRows);
   TRACE("CoolSwitchColumns: %d\n", CoolSwitchColumns);

   return TRUE;
}