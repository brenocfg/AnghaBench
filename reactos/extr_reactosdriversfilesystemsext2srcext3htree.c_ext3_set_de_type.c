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
typedef  int /*<<< orphan*/  umode_t ;
struct super_block {int dummy; } ;
struct ext3_dir_entry_2 {int /*<<< orphan*/  file_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_FILETYPE ; 
 scalar_t__ EXT3_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_type_by_mode (int /*<<< orphan*/ ) ; 

void ext3_set_de_type(struct super_block *sb,
                      struct ext3_dir_entry_2 *de,
                      umode_t mode)
{
    if (EXT3_HAS_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_FILETYPE))
        de->file_type = ext3_type_by_mode(mode);
}