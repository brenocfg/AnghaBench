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
struct TYPE_3__ {int Signature1; int BytesPerSector; int FATCount; int Media; int SectorsPerCluster; } ;
typedef  TYPE_1__* PFATBootSector ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL CheckAgainstFAT(PFATBootSector Sector)
{
    if (Sector->Signature1 != 0xaa55)
    {
        return FALSE;
    }

    if (Sector->BytesPerSector != 512 &&
        Sector->BytesPerSector != 1024 &&
        Sector->BytesPerSector != 2048 &&
        Sector->BytesPerSector != 4096)
    {
        return FALSE;
    }

    if (Sector->FATCount != 1 &&
        Sector->FATCount != 2)
    {
        return FALSE;
    }

    if (Sector->Media != 0xf0 &&
        Sector->Media != 0xf8 &&
        Sector->Media != 0xf9 &&
        Sector->Media != 0xfa &&
        Sector->Media != 0xfb &&
        Sector->Media != 0xfc &&
        Sector->Media != 0xfd &&
        Sector->Media != 0xfe &&
        Sector->Media != 0xff)
    {
        return FALSE;
    }

    if (Sector->SectorsPerCluster != 1 &&
        Sector->SectorsPerCluster != 2 &&
        Sector->SectorsPerCluster != 4 &&
        Sector->SectorsPerCluster != 8 &&
        Sector->SectorsPerCluster != 16 &&
        Sector->SectorsPerCluster != 32 &&
        Sector->SectorsPerCluster != 64 &&
        Sector->SectorsPerCluster != 128)
    {
        return FALSE;
    }

    if (Sector->BytesPerSector * Sector->SectorsPerCluster > 32 * 1024)
    {
        return FALSE;
    }

    return TRUE;
}