#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  SectorSize; } ;
struct TYPE_6__ {int /*<<< orphan*/  str; scalar_t__ (* fn ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {char* _handle; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAKE_FD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__ SelectedDrive ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_br (int /*<<< orphan*/ *) ; 
 scalar_t__ is_fat_16_br (int /*<<< orphan*/ *) ; 
 scalar_t__ is_fat_32_br (int /*<<< orphan*/ *) ; 
 TYPE_2__* known_pbr ; 
 int /*<<< orphan*/  set_bytes_per_sector (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprintf (char*,char const*,...) ; 

BOOL AnalyzePBR(HANDLE hLogicalVolume)
{
	const char* pbr_name = "Partition Boot Record";
	FAKE_FD fake_fd = { 0 };
	FILE* fp = (FILE*)&fake_fd;
	int i;

	fake_fd._handle = (char*)hLogicalVolume;
	set_bytes_per_sector(SelectedDrive.SectorSize);

	if (!is_br(fp)) {
		uprintf("Volume does not have an x86 %s", pbr_name);
		return FALSE;
	}

	if (is_fat_16_br(fp) || is_fat_32_br(fp)) {
		for (i=0; i<ARRAYSIZE(known_pbr); i++) {
			if (known_pbr[i].fn(fp)) {
				uprintf("Drive has a %s %s", known_pbr[i].str, pbr_name);
				return TRUE;
			}
		}
		uprintf("Volume has an unknown FAT16 or FAT32 %s", pbr_name);
	} else {
		uprintf("Volume has an unknown %s", pbr_name);
	}
	return TRUE;
}