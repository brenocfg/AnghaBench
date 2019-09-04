#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_16__ {scalar_t__ Count; TYPE_3__* PartialDescriptors; } ;
struct TYPE_19__ {TYPE_4__ PartialResourceList; } ;
struct TYPE_18__ {scalar_t__ Size; int Node; } ;
struct TYPE_17__ {char* Signature; } ;
struct TYPE_13__ {int DataSize; } ;
struct TYPE_14__ {TYPE_1__ DeviceSpecificData; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
typedef  TYPE_5__* PCM_PNP_BIOS_INSTALLATION_CHECK ;
typedef  TYPE_6__* PCM_PNP_BIOS_DEVICE_NODE ;
typedef  TYPE_7__* PCM_FULL_RESOURCE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CM_PNP_BIOS_INSTALLATION_CHECK ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_DESCRIPTOR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetPnpKey (scalar_t__*) ; 
 int /*<<< orphan*/  PrintDeviceData (TYPE_6__*) ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegQueryValueEx (scalar_t__,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 int /*<<< orphan*/  getch () ; 
 TYPE_7__* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_7__* realloc (TYPE_7__*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int main (int argc, char *argv[])
{
  LONG lError;
  HKEY hPnpKey;
  DWORD dwType;
  DWORD dwSize;
  BOOL Ask;
  PCM_FULL_RESOURCE_DESCRIPTOR lpBuffer;
  PCM_PNP_BIOS_INSTALLATION_CHECK lpPnpInst;
  PCM_PNP_BIOS_DEVICE_NODE lpDevNode;
  DWORD dwDataSize;
  DWORD dwResourceSize;

  hPnpKey = 0;

  Ask = TRUE;
  if (argc >1 && (!strcmp(argv[1],"/S") || !strcmp(argv[1],"/s")))
    {
      Ask = FALSE;
    }

  if (argc >1 && !strcmp(argv[1],"/?"))
    {
      printf("This utility prints the PnP-nodes from the registry\n");
      printf("\"/s\" prevents the \"Press any key\"\n\n");
      return 0;
    }

  lError = GetPnpKey(&hPnpKey);
  if (lError != ERROR_SUCCESS)
    {
      printf("Failed to get PnP-BIOS key\n");
      return 0;
    }

  if (hPnpKey != 0)
    {
      printf("Found PnP-BIOS key\n");
    }

  /* Allocate buffer */
  dwSize = 2048;
  lpBuffer = malloc(dwSize);
  if (lpBuffer == NULL)
    {
      printf("Error: malloc() failed\n");
      RegCloseKey(hPnpKey);
      return 0;
    }

  do
    {
      lError = RegQueryValueEx(hPnpKey,
			       "Configuration Data",
			       NULL,
			       &dwType,
			       (LPBYTE)lpBuffer,
			       &dwSize);
      if (lError == ERROR_MORE_DATA)
        {
          lpBuffer = realloc(lpBuffer, dwSize);
          if (lpBuffer == NULL)
            {
              printf("Error: realloc() of %u bytes failed\n", (unsigned) dwSize);
              RegCloseKey(hPnpKey);
              return 0;
            }
        }
    }
  while (lError == ERROR_MORE_DATA);
  if (lError != ERROR_SUCCESS)
    {
      printf("Failed to read 'Configuration Data' value\n");
      free(lpBuffer);
      RegCloseKey(hPnpKey);
      return 0;
    }

//  printf ("Data size: %lu\n", dwSize);

  RegCloseKey(hPnpKey);

//  printf("Resource count %lu\n", lpBuffer->PartialResourceList.Count);

  if (lpBuffer->PartialResourceList.Count == 0)
    {
      printf("Invalid resource count!\n");
      free(lpBuffer);
      return 0;
    }

//  printf("lpBuffer %p\n", lpBuffer);

  dwResourceSize = lpBuffer->PartialResourceList.PartialDescriptors[0].u.DeviceSpecificData.DataSize;
//  printf("ResourceSize: %lu\n", dwResourceSize);

  lpPnpInst = (PCM_PNP_BIOS_INSTALLATION_CHECK)
	((ULONG_PTR)(&lpBuffer->PartialResourceList.PartialDescriptors[0]) +
	  sizeof(CM_PARTIAL_RESOURCE_DESCRIPTOR));

//  printf("lpPnpInst %p\n", lpPnpInst);

  printf("Signature '%.4s'\n", lpPnpInst->Signature);
  if (strncmp((PCHAR)lpPnpInst->Signature, "$PnP", 4))
    {
      printf("Error: Invalid PnP signature\n");
      free(lpBuffer);
      return 0;
    }

//  printf("InstCheck length: %lu\n", lpPnpInst->Length);

  dwDataSize = sizeof(CM_PNP_BIOS_INSTALLATION_CHECK);
  lpDevNode = (PCM_PNP_BIOS_DEVICE_NODE)((DWORD)lpPnpInst + sizeof(CM_PNP_BIOS_INSTALLATION_CHECK));

  if (lpDevNode->Size == 0)
    {
      printf("Error: Device node size is zero!\n");
      return 0;
    }

#if 0
      printf("Node: %x  Size %hu (0x%hx)\n",
	      lpDevNode->Node,
	      lpDevNode->Size,
	      lpDevNode->Size);

  printf("Done.\n");
return 0;
#endif


  while (dwDataSize < dwResourceSize)
    {
      if (lpDevNode->Size == 0)
	break;

      printf("Node: %x  Size %hu (0x%hx)\n",
	     lpDevNode->Node,
	     lpDevNode->Size,
	     lpDevNode->Size);

      dwDataSize += lpDevNode->Size;
      lpDevNode = (PCM_PNP_BIOS_DEVICE_NODE)((DWORD)lpDevNode + lpDevNode->Size);
    }

  if (Ask)
    {
      printf("\n Press any key...\n");
      getch();
    }
  else
    {
      printf("\n");
    }

  dwDataSize = sizeof(CM_PNP_BIOS_INSTALLATION_CHECK);
  lpDevNode = (PCM_PNP_BIOS_DEVICE_NODE)((DWORD)lpPnpInst + sizeof(CM_PNP_BIOS_INSTALLATION_CHECK));

  while (dwDataSize < dwResourceSize)
    {
      if (lpDevNode->Size == 0)
	break;

      PrintDeviceData(lpDevNode);

      if (Ask)
        {
          printf("\n Press any key...\n");
          getch();
        }
      else
        {
          printf("\n");
        }

      dwDataSize += lpDevNode->Size;
      lpDevNode = (PCM_PNP_BIOS_DEVICE_NODE)((DWORD)lpDevNode + lpDevNode->Size);
    }

  free(lpBuffer);

  return 0;
}