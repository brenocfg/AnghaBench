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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IMMDevice ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceHotplugReport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MMThread_DevicesEnum_Added(void *data, LPCWSTR wid, IMMDevice *dev)
{
    audio_output_t *aout = data;

    DeviceHotplugReport(aout, wid, dev);
}