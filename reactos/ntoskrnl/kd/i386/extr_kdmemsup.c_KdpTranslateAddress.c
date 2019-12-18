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
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int* PULONG_PTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BIG_PAGE_SIZE ; 
 int CR4_PAGE_SIZE_BIT ; 
 int /*<<< orphan*/  FALSE ; 
 int KdpPhysRead (int,int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PAGE_TABLE_MASK ; 
 int PDE_PRESENT_BIT ; 
 int PDE_PS_BIT ; 
 int /*<<< orphan*/  TRUE ; 
 int __readcr3 () ; 
 int __readcr4 () ; 

__attribute__((used)) static
BOOLEAN
KdpTranslateAddress(ULONG_PTR Addr, PULONG_PTR ResultAddr)
{
    ULONG_PTR CR3Value = __readcr3();
    ULONG_PTR CR4Value = __readcr4();
    ULONG_PTR PageDirectory = (CR3Value & ~(PAGE_SIZE-1)) +
        ((Addr >> 22) * sizeof(ULONG));
    ULONG_PTR PageDirectoryEntry = KdpPhysRead(PageDirectory, sizeof(ULONG));

    /* Not present -> fail */
    if (!(PageDirectoryEntry & PDE_PRESENT_BIT))
    {
        return FALSE;
    }

    /* Big Page? */
    if ((PageDirectoryEntry & PDE_PS_BIT) && (CR4Value & CR4_PAGE_SIZE_BIT))
    {
        *ResultAddr = (PageDirectoryEntry & ~(BIG_PAGE_SIZE-1)) +
            (Addr & (BIG_PAGE_SIZE-1));
        return TRUE;
    }
    else
    {
        ULONG_PTR PageTableAddr =
            (PageDirectoryEntry & ~(PAGE_SIZE-1)) +
            ((Addr >> PAGE_SHIFT) & PAGE_TABLE_MASK) * sizeof(ULONG);
        ULONG_PTR PageTableEntry = KdpPhysRead(PageTableAddr, sizeof(ULONG));
        if (PageTableEntry & PDE_PRESENT_BIT)
        {
            *ResultAddr = (PageTableEntry & ~(PAGE_SIZE-1)) +
                (Addr & (PAGE_SIZE-1));
            return TRUE;
        }
    }

    return FALSE;
}