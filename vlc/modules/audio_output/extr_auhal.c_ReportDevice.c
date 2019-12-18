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
typedef  int /*<<< orphan*/  audio_output_t ;
typedef  int UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  aout_HotplugReport (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
ReportDevice(audio_output_t *p_aout, UInt32 i_id, const char *name)
{
    char deviceid[10];
    sprintf(deviceid, "%i", i_id);

    aout_HotplugReport(p_aout, deviceid, name);
}