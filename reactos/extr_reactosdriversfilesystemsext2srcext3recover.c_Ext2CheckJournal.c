#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext3_super_block {scalar_t__ s_journal_inum; scalar_t__ s_journal_dev; int /*<<< orphan*/  s_feature_incompat; } ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; scalar_t__ SuperBlock; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PEXT2_VCB ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IsFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsVcbReadOnly (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLongFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VCB_JOURNAL_RECOVER ; 

INT
Ext2CheckJournal(
    PEXT2_VCB          Vcb,
    PULONG             jNo
)
{
    struct ext3_super_block* esb = NULL;

    /* check ext3 super block */
    esb = (struct ext3_super_block *)Vcb->SuperBlock;
    if (IsFlagOn(esb->s_feature_incompat,
                 EXT3_FEATURE_INCOMPAT_RECOVER)) {
        SetLongFlag(Vcb->Flags, VCB_JOURNAL_RECOVER);
    }

    /* must stop here if volume is read-only */
    if (IsVcbReadOnly(Vcb)) {
        goto errorout;
    }

    /* journal is external ? */
    if (esb->s_journal_inum == 0) {
        goto errorout;
    }

    /* oops: volume is corrupted */
    if (esb->s_journal_dev) {
        goto errorout;
    }

    /* return the journal inode number */
    *jNo = esb->s_journal_inum;

    return TRUE;

errorout:

    return FALSE;
}