#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* pTW_IDENTITY ;
struct TYPE_15__ {int /*<<< orphan*/  ProductName; scalar_t__ Id; } ;
struct TYPE_17__ {scalar_t__ (* dsEntry ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;int /*<<< orphan*/ * event_window; int /*<<< orphan*/ * ui_window; int /*<<< orphan*/  pending_messages; TYPE_2__ identity; struct TYPE_17__* next; scalar_t__ hmod; } ;
typedef  TYPE_4__ activeDS ;
struct TYPE_14__ {int /*<<< orphan*/  ProductName; } ;
struct TYPE_18__ {int /*<<< orphan*/  modname; TYPE_1__ identity; } ;
struct TYPE_16__ {char* ProductName; scalar_t__ Id; } ;
typedef  size_t TW_UINT16 ;
typedef  int /*<<< orphan*/  TW_MEMREF ;
typedef  scalar_t__ HMODULE ;
typedef  scalar_t__ (* DSENTRYPROC ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ;

/* Variables and functions */
 int /*<<< orphan*/  DAT_IDENTITY ; 
 int /*<<< orphan*/  DG_CONTROL ; 
 int /*<<< orphan*/  DSM_initialized ; 
 int /*<<< orphan*/  DSM_sourceId ; 
 int /*<<< orphan*/  DSM_twCC ; 
 int /*<<< orphan*/  ERR (char*,char const*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ LoadLibraryA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_OPENDS ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TWCC_LOWMEMORY ; 
 int /*<<< orphan*/  TWCC_NODS ; 
 int /*<<< orphan*/  TWCC_OPERATIONERROR ; 
 int /*<<< orphan*/  TWCC_SEQERROR ; 
 int /*<<< orphan*/  TWCC_SUCCESS ; 
 size_t TWRC_FAILURE ; 
 scalar_t__ TWRC_SUCCESS ; 
 TYPE_4__* activeSources ; 
 TYPE_9__* devices ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 size_t nrdevices ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  twain_autodetect () ; 

TW_UINT16 TWAIN_OpenDS (pTW_IDENTITY pOrigin, TW_MEMREF pData)
{
	TW_UINT16 i = 0;
	pTW_IDENTITY pIdentity = (pTW_IDENTITY) pData;
	activeDS *newSource;
	const char *modname = NULL;
	HMODULE hmod;

	TRACE("DG_CONTROL/DAT_IDENTITY/MSG_OPENDS\n");
        TRACE("pIdentity is %s\n", pIdentity->ProductName);
	if (!DSM_initialized) {
		FIXME("seq error\n");
		DSM_twCC = TWCC_SEQERROR;
		return TWRC_FAILURE;
	}
	twain_autodetect();
	if (!nrdevices) {
		FIXME("no devs.\n");
		DSM_twCC = TWCC_NODS;
		return TWRC_FAILURE;
	}

	if (pIdentity->ProductName[0] != '\0') {
		/* Make sure the source to be opened exists in the device list */
		for (i = 0; i<nrdevices; i++)
			if (!strcmp (devices[i].identity.ProductName, pIdentity->ProductName))
				break;
		if (i == nrdevices)
			i = 0;
	} /* else use the first device */

	/* the source is found in the device list */
	newSource = HeapAlloc (GetProcessHeap(), 0, sizeof (activeDS));
	if (!newSource) {
		DSM_twCC = TWCC_LOWMEMORY;
		FIXME("Out of memory.\n");
		return TWRC_FAILURE;
	}
	hmod = LoadLibraryA(devices[i].modname);
	if (!hmod) {
		ERR("Failed to load TWAIN Source %s\n", modname);
		DSM_twCC = TWCC_OPERATIONERROR;
                HeapFree(GetProcessHeap(), 0, newSource);
		return TWRC_FAILURE;
	}
	newSource->hmod = hmod; 
	newSource->dsEntry = (DSENTRYPROC)GetProcAddress(hmod, "DS_Entry"); 
	/* Assign id for the opened data source */
	pIdentity->Id = DSM_sourceId ++;
	if (TWRC_SUCCESS != newSource->dsEntry (pOrigin, DG_CONTROL, DAT_IDENTITY, MSG_OPENDS, pIdentity)) {
		DSM_twCC = TWCC_OPERATIONERROR;
                HeapFree(GetProcessHeap(), 0, newSource);
                DSM_sourceId--;
		return TWRC_FAILURE;
	}
	/* add the data source to an internal active source list */
	newSource->next = activeSources;
	newSource->identity.Id = pIdentity->Id;
	strcpy (newSource->identity.ProductName, pIdentity->ProductName);
        list_init(&newSource->pending_messages);
        newSource->ui_window = NULL;
        newSource->event_window = NULL;
	activeSources = newSource;
	DSM_twCC = TWCC_SUCCESS;
	return TWRC_SUCCESS;
}