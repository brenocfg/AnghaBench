#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* emh; scalar_t__ hFile; } ;
struct TYPE_12__ {int nSize; int /*<<< orphan*/  iType; } ;
struct TYPE_11__ {int nBytes; int /*<<< orphan*/  nRecords; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ ENHMETAHEADER ;
typedef  TYPE_2__ EMR ;
typedef  TYPE_3__ EMFDRV_PDEVICE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,TYPE_2__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* get_emf_physdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

BOOL EMFDRV_WriteRecord( PHYSDEV dev, EMR *emr )
{
    DWORD len;
    DWORD bytes_written;
    ENHMETAHEADER *emh;
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );

    TRACE("record %d, size %d %s\n",
          emr->iType, emr->nSize, physDev->hFile ? "(to disk)" : "");

    assert( !(emr->nSize & 3) );

    physDev->emh->nBytes += emr->nSize;
    physDev->emh->nRecords++;

    if(physDev->hFile) {
        if (!WriteFile(physDev->hFile, emr, emr->nSize, &bytes_written, NULL))
	    return FALSE;
    } else {
        DWORD nEmfSize = HeapSize(GetProcessHeap(), 0, physDev->emh);
        len = physDev->emh->nBytes;
        if (len > nEmfSize) {
            nEmfSize += (nEmfSize / 2) + emr->nSize;
            emh = HeapReAlloc(GetProcessHeap(), 0, physDev->emh, nEmfSize);
            if (!emh) return FALSE;
            physDev->emh = emh;
        }
        memcpy((CHAR *)physDev->emh + physDev->emh->nBytes - emr->nSize, emr,
               emr->nSize);
    }
    return TRUE;
}