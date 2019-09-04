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
struct TYPE_3__ {int j_format_version; int /*<<< orphan*/ * j_superblock; } ;
typedef  TYPE_1__ journal_t ;
typedef  int /*<<< orphan*/  journal_superblock_t ;

/* Variables and functions */
 unsigned long JFS_KNOWN_COMPAT_FEATURES ; 
 unsigned long JFS_KNOWN_INCOMPAT_FEATURES ; 
 unsigned long JFS_KNOWN_ROCOMPAT_FEATURES ; 

int journal_check_available_features (journal_t *journal, unsigned long compat,
                                      unsigned long ro, unsigned long incompat)
{
    journal_superblock_t *sb;

    if (!compat && !ro && !incompat)
        return 1;

    sb = journal->j_superblock;

    /* We can support any known requested features iff the
     * superblock is in version 2.  Otherwise we fail to support any
     * extended sb features. */

    if (journal->j_format_version != 2)
        return 0;

    if ((compat   & JFS_KNOWN_COMPAT_FEATURES) == compat &&
            (ro       & JFS_KNOWN_ROCOMPAT_FEATURES) == ro &&
            (incompat & JFS_KNOWN_INCOMPAT_FEATURES) == incompat)
        return 1;

    return 0;
}