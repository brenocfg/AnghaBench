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
typedef  scalar_t__* PHKEY ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegOpenKey (scalar_t__,char*,scalar_t__*) ; 
 scalar_t__ RegQueryValueEx (scalar_t__,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ stricmp (char*,char*) ; 

LONG
GetPnpKey(PHKEY PnpKey)
{
  LONG lError;
  char szBuffer[80];
  HKEY hAdapterKey;
  HKEY hBusKey;
  DWORD dwBus;
  DWORD dwType;
  DWORD dwSize;

  *PnpKey = 0;

  lError = RegOpenKey(HKEY_LOCAL_MACHINE,
		      "HARDWARE\\DESCRIPTION\\System\\MultifunctionAdapter",
		      &hAdapterKey);
  if (lError != ERROR_SUCCESS)
    return 0;

  /* Enumerate buses */
  for (dwBus = 0; ; dwBus++)
    {
      sprintf(szBuffer, "%lu", dwBus);

      lError = RegOpenKey(hAdapterKey,
			  szBuffer,
			  &hBusKey);
      if (lError != ERROR_SUCCESS)
	{
	  RegCloseKey(hAdapterKey);
	  return lError;
	}

      dwSize = 80;
      lError = RegQueryValueEx(hBusKey,
			       "Identifier",
			       NULL,
			       &dwType,
			       (LPBYTE)szBuffer,
			       &dwSize);
      if (lError != ERROR_SUCCESS)
	{
	  RegCloseKey(hBusKey);
	  RegCloseKey(hAdapterKey);
	  return lError;
	}

      if (dwType == REG_SZ && stricmp(szBuffer, "pnp bios") == 0)
	{
	  *PnpKey = hBusKey;
	  RegCloseKey(hAdapterKey);
	  return ERROR_SUCCESS;
	}

      RegCloseKey(hBusKey);
    }

  return 1;
}