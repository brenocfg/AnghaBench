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
struct boot_sector_16 {int reserved3; int reserved2; } ;
struct boot_sector {int reserved3; int reserved2; } ;
struct TYPE_3__ {int fat_bits; } ;
typedef  TYPE_1__ DOS_FS ;

/* Variables and functions */
 int FAT_STATE_DIRTY ; 
 int /*<<< orphan*/  fs_write (int /*<<< orphan*/ ,int,struct boot_sector_16*) ; 
 char print_fat_dirty_state () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void check_fat_state_bit(DOS_FS * fs, void *b)
{
    if (fs->fat_bits == 32) {
	struct boot_sector *b32 = b;

	if (b32->reserved3 & FAT_STATE_DIRTY) {
	    printf("0x41: ");
	    if (print_fat_dirty_state() == '1') {
		b32->reserved3 &= ~FAT_STATE_DIRTY;
		fs_write(0, sizeof(*b32), b32);
	    }
	}
    } else {
	struct boot_sector_16 *b16 = b;

	if (b16->reserved2 & FAT_STATE_DIRTY) {
	    printf("0x25: ");
	    if (print_fat_dirty_state() == '1') {
		b16->reserved2 &= ~FAT_STATE_DIRTY;
		fs_write(0, sizeof(*b16), b16);
	    }
	}
    }
}