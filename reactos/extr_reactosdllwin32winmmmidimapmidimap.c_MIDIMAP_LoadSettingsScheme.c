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
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  const WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ ** ChannelMap; } ;
typedef  TYPE_1__ MIDIMAPDATA ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  MIDIMAP_FindPort (int /*<<< orphan*/  const*,unsigned int*) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegEnumKeyW (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,void*,int*) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,void*,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * midiOutPorts ; 

__attribute__((used)) static BOOL	MIDIMAP_LoadSettingsScheme(MIDIMAPDATA* mom, const WCHAR* scheme)
{
    HKEY	hSchemesKey, hKey, hPortKey;
    unsigned	i, idx, dev;
    WCHAR       buffer[256], port[256];
    DWORD	type, size, mask;

    for (i = 0; i < 16; i++)	mom->ChannelMap[i] = NULL;

    if (RegOpenKeyA(HKEY_LOCAL_MACHINE,
		    "System\\CurrentControlSet\\Control\\MediaProperties\\PrivateProperties\\Midi\\Schemes",
		    &hSchemesKey))
    {
	return FALSE;
    }
    if (RegOpenKeyW(hSchemesKey, scheme, &hKey))
    {
	RegCloseKey(hSchemesKey);
	return FALSE;
    }

    for (idx = 0; !RegEnumKeyW(hKey, idx, buffer, sizeof(buffer)); idx++)
    {
	if (RegOpenKeyW(hKey, buffer, &hPortKey)) continue;

	size = sizeof(port);
	if (RegQueryValueExW(hPortKey, NULL, 0, &type, (void*)port, &size)) continue;

	if (!MIDIMAP_FindPort(port, &dev)) continue;

	size = sizeof(mask);
	if (RegQueryValueExA(hPortKey, "Channels", 0, &type, (void*)&mask, &size))
	    continue;

	for (i = 0; i < 16; i++)
	{
	    if (mask & (1 << i))
	    {
		if (mom->ChannelMap[i])
		    ERR("Quirks in registry, channel %u is mapped twice\n", i);
		mom->ChannelMap[i] = &midiOutPorts[dev];
	    }
	}
    }

    RegCloseKey(hSchemesKey);
    RegCloseKey(hKey);

    return TRUE;
}