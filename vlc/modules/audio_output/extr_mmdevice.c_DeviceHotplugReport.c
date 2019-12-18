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
 char* DeviceGetFriendlyName (int /*<<< orphan*/ *) ; 
 char* FromWide (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_HotplugReport (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int DeviceHotplugReport(audio_output_t *aout, LPCWSTR wid,
                               IMMDevice *dev)
{
    char *id = FromWide(wid);
    if (!id)
        return VLC_EGENERIC;

    char *name = DeviceGetFriendlyName(dev);
    if (name == NULL)
        name = id;

    aout_HotplugReport(aout, id, name);

    free(id);
    if (id != name)
        free(name);
    return VLC_SUCCESS;
}