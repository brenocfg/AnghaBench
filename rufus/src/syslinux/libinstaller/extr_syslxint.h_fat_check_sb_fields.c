#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  FileSysType; } ;
struct TYPE_4__ {int /*<<< orphan*/  FileSysType; } ;
struct fat_boot_sector {TYPE_1__ bs32; TYPE_2__ bs16; scalar_t__ bsFATs; scalar_t__ bsResSectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline int fat_check_sb_fields(const struct fat_boot_sector *sb)
{
    return sb->bsResSectors && sb->bsFATs &&
            (!memcmp(sb->bs16.FileSysType, "FAT12   ", 8) ||
             !memcmp(sb->bs16.FileSysType, "FAT16   ", 8) ||
             !memcmp(sb->bs16.FileSysType, "FAT     ", 8) ||
             !memcmp(sb->bs32.FileSysType, "FAT32   ", 8));
}