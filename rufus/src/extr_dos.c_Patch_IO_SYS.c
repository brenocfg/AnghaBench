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
typedef  int /*<<< orphan*/  expected ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int* DiskImage ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

__attribute__((used)) static BOOL Patch_IO_SYS(size_t filestart, size_t filesize)
{
	const BYTE expected[8] = { 0xFA, 0x80, 0x75, 0x09, 0x8D, 0xB6, 0x99, 0x00 };

	uprintf("Patching IO.SYS...\n");
	if (filesize != 116736) {
		uprintf("  unexpected file size\n");
		return FALSE;
	}
	if (memcmp(&DiskImage[filestart+0x3a8], expected, sizeof(expected)) != 0) {
		uprintf("  unexpected binary data\n");
		return FALSE;
	}
	DiskImage[filestart+0x3aa] = 0xeb;
	return TRUE;
}