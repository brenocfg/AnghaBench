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
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_HYPERSPACE (scalar_t__) ; 
 int /*<<< orphan*/  MmDeleteHyperspaceMapping (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_ROUND_DOWN (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN MmUnmapPageTable(PULONG Pt)
{
    if (!IS_HYPERSPACE(Pt))
    {
        return TRUE;
    }

    if (Pt)
    {
        MmDeleteHyperspaceMapping((PVOID)PAGE_ROUND_DOWN(Pt));
    }
    return FALSE;
}