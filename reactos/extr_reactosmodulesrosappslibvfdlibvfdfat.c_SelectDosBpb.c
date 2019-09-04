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
typedef  int /*<<< orphan*/  bpb_tbl ;
typedef  scalar_t__ USHORT ;
struct TYPE_3__ {int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; scalar_t__ SmallSectors; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  const member_0; } ;
typedef  TYPE_1__ DOS_BPB ;

/* Variables and functions */
#define  VFD_BYTES_PER_SECTOR 128 

__attribute__((used)) static const DOS_BPB *SelectDosBpb(
	USHORT	nSectors)
{
	static const DOS_BPB bpb_tbl[] = {
		// b/s				  s/c r fat root  sec  desc s/f s/t  h
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112,  320, 0xFE,  1,  8, 1, 0, 0},	// 160KB 5.25"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112,  360, 0xFC,  1,  9, 1, 0, 0},	// 180KB 5.25"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112,  640, 0xFF,  1,  8, 2, 0, 0},	// 320KB 5.25"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112,  720, 0xFD,  2,  9, 2, 0, 0},	// 360KB 5.25"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112, 1280, 0xFB,  2,  8, 2, 0, 0},	// 640KB 5.25" / 3.5"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112, 1440, 0xF9,  3,  9, 2, 0, 0},	// 720KB 5.25" / 3.5"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 112, 1640, 0xF9,  3, 10, 2, 0, 0},	// 820KB 3.5"
		{VFD_BYTES_PER_SECTOR, 1, 1, 2, 224, 2400, 0xF9,  7, 15, 2, 0, 0},	// 1.20MB 5.25" / 3.5"
		{VFD_BYTES_PER_SECTOR, 1, 1, 2, 224, 2880, 0xF0,  9, 18, 2, 0, 0},	// 1.44MB 3.5"
		{VFD_BYTES_PER_SECTOR, 1, 1, 2, 224, 3360, 0xF0, 10, 21, 2, 0, 0},	// 1.68MB 3.5"
		{VFD_BYTES_PER_SECTOR, 1, 1, 2, 224, 3444, 0xF0, 10, 21, 2, 0, 0},	// 1.72MB 3.5"
		{VFD_BYTES_PER_SECTOR, 2, 1, 2, 240, 5760, 0xF0,  9, 36, 2, 0, 0},	// 2.88MB 3.5"
	};

	int i;

	for (i = 0; i < sizeof(bpb_tbl) / sizeof(bpb_tbl[0]); i++) {
		if (nSectors == bpb_tbl[i].SmallSectors) {
			return &bpb_tbl[i];
		}
	}

	return NULL;
}