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
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__* Unused0; scalar_t__* Unused3; int BytesPerSector; int SectorsPerCluster; int /*<<< orphan*/  OEMID; } ;
typedef  TYPE_1__* PNTFSBootSector ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int RtlCompareMemory (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL CheckAgainstNTFS(PNTFSBootSector Sector)
{
    ULONG k;
    ULONG ClusterSize;

    /* OEMID: this field must be NTFS */
    if (RtlCompareMemory(Sector->OEMID, "NTFS    ", 8) != 8)
    {
        return FALSE;
    }

    /* Unused0: this field must be COMPLETELY null */
    for (k = 0; k < 7; k++)
    {
        if (Sector->Unused0[k] != 0)
        {
            return FALSE;
        }
    }

    /* Unused3: this field must be COMPLETELY null */
    for (k = 0; k < 4; k++)
    {
        if (Sector->Unused3[k] != 0)
        {
            return FALSE;
        }
    }

    /* Check cluster size */
    ClusterSize = Sector->BytesPerSector * Sector->SectorsPerCluster;
    if (ClusterSize != 512 && ClusterSize != 1024 && 
        ClusterSize != 2048 && ClusterSize != 4096 &&
        ClusterSize != 8192 && ClusterSize != 16384 &&
        ClusterSize != 32768 && ClusterSize != 65536)
    {
        return FALSE;
    }

    return TRUE;
}