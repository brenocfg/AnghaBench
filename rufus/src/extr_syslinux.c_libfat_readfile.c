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
typedef  scalar_t__ libfat_sector_t ;
struct TYPE_3__ {size_t QuadPart; } ;
typedef  size_t LONGLONG ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,void*,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointerEx (int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  uprintf (char*,size_t,size_t,...) ; 

int libfat_readfile(intptr_t pp, void *buf, size_t secsize, libfat_sector_t sector)
{
	LARGE_INTEGER offset;
	DWORD bytes_read;

	offset.QuadPart = (LONGLONG) sector * secsize;
	if (!SetFilePointerEx((HANDLE) pp, offset, NULL, FILE_BEGIN)) {
		uprintf("Could not set pointer to position %llu: %s", offset.QuadPart, WindowsErrorString());
		return 0;
	}

	if (!ReadFile((HANDLE) pp, buf, (DWORD) secsize, &bytes_read, NULL)) {
		uprintf("Could not read sector %llu: %s", sector, WindowsErrorString());
		return 0;
	}

	if (bytes_read != secsize) {
		uprintf("Sector %llu: Read %d bytes instead of %d requested", sector, bytes_read, secsize);
		return 0;
	}

	return (int)secsize;
}