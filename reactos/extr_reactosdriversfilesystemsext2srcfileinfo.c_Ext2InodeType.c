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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PEXT2_MCB ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FT_DIR ; 
 int /*<<< orphan*/  EXT2_FT_REG_FILE ; 
 int /*<<< orphan*/  EXT2_FT_SYMLINK ; 
 scalar_t__ IsMcbDirectory (int /*<<< orphan*/ ) ; 
 scalar_t__ IsMcbSymLink (int /*<<< orphan*/ ) ; 

ULONG
Ext2InodeType(PEXT2_MCB Mcb)
{
    if (IsMcbSymLink(Mcb)) {
        return EXT2_FT_SYMLINK;
    }

    if (IsMcbDirectory(Mcb)) {
        return EXT2_FT_DIR;
    }

    return EXT2_FT_REG_FILE;
}