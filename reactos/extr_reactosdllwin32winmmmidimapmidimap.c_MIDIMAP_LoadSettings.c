#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
struct TYPE_7__ {TYPE_1__** ChannelMap; } ;
struct TYPE_6__ {int uDevID; } ;
typedef  TYPE_2__ MIDIMAPDATA ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int MIDIMAP_LoadSettingsDefault (TYPE_2__*,char*) ; 
 int MIDIMAP_LoadSettingsScheme (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,void*,int*) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,void*,int*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,int) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msacm ; 

__attribute__((used)) static BOOL	MIDIMAP_LoadSettings(MIDIMAPDATA* mom)
{
    HKEY 	hKey;
    BOOL	ret;

    if (RegOpenKeyA(HKEY_CURRENT_USER,
		    "Software\\Microsoft\\Windows\\CurrentVersion\\Multimedia\\MIDIMap", &hKey))
    {
	ret = MIDIMAP_LoadSettingsDefault(mom, NULL);
    }
    else
    {
	DWORD	type, size, out;
	WCHAR   buffer[256];

	ret = 2;
	size = sizeof(out);
	if (!RegQueryValueExA(hKey, "UseScheme", 0, &type, (void*)&out, &size) && out)
	{
            static const WCHAR cs[] = {'C','u','r','r','e','n','t','S','c','h','e','m','e',0};
	    size = sizeof(buffer);
	    if (!RegQueryValueExW(hKey, cs, 0, &type, (void*)buffer, &size))
	    {
		if (!(ret = MIDIMAP_LoadSettingsScheme(mom, buffer)))
		    ret = MIDIMAP_LoadSettingsDefault(mom, NULL);
	    }
	    else
	    {
		ERR("Wrong registry: UseScheme is active, but no CurrentScheme found\n");
	    }
	}
	if (ret == 2)
	{
            static const WCHAR ci[] = {'C','u','r','r','e','n','t','I','n','s','t','r','u','m','e','n','t',0};
	    size = sizeof(buffer);
	    if (!RegQueryValueExW(hKey, ci, 0, &type, (void*)buffer, &size) && *buffer)
	    {
		ret = MIDIMAP_LoadSettingsDefault(mom, buffer);
	    }
	    else if (!RegQueryValueExW(hKey, L"szPname", 0, &type, (void*)buffer, &size) && *buffer)
	    {
		/* Windows XP and higher setting */
		ret = MIDIMAP_LoadSettingsDefault(mom, buffer);
	    }
	    else
	    {
		ret = MIDIMAP_LoadSettingsDefault(mom, NULL);
	    }
	}
    }
    RegCloseKey(hKey);

    if (ret && TRACE_ON(msacm))
    {
	unsigned	i;

	for (i = 0; i < 16; i++)
	{
	    TRACE("chnMap[%2d] => %d\n",
		  i, mom->ChannelMap[i] ? mom->ChannelMap[i]->uDevID : -1);
	}
    }
    return ret;
}