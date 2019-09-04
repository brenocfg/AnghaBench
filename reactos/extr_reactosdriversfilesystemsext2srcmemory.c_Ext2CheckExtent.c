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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PLARGE_MCB ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */

VOID
Ext2CheckExtent(
    PLARGE_MCB  Zone,
    LONGLONG    Vbn,
    LONGLONG    Lbn,
    LONGLONG    Length,
    BOOLEAN     bAdded
)
{
#if EXT2_DEBUG
    LONGLONG    DirtyLbn;
    LONGLONG    DirtyLen;
    LONGLONG    RunStart;
    LONGLONG    RunLength;
    ULONG       Index;
    BOOLEAN     bFound = FALSE;

    bFound = FsRtlLookupLargeMcbEntry(
                 Zone,
                 Vbn,
                 &DirtyLbn,
                 &DirtyLen,
                 &RunStart,
                 &RunLength,
                 &Index );

    if (!bAdded && (!bFound || DirtyLbn == -1)) {
        return;
    }

    if ( !bFound || (DirtyLbn == -1) ||
            (DirtyLbn != Lbn) ||
            (DirtyLen < Length)) {

        DbgBreak();

        for (Index = 0; TRUE; Index++) {

            if (!FsRtlGetNextLargeMcbEntry(
                        Zone,
                        Index,
                        &Vbn,
                        &Lbn,
                        &Length)) {
                break;
            }

            DEBUG(DL_EXT, ("Index = %xh Vbn = %I64xh Lbn = %I64xh Len = %I64xh\n",
                           Index, Vbn, Lbn, Length ));
        }
    }
#endif
}