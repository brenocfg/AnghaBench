#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int loff_t ;
typedef  int /*<<< orphan*/  geom ;
struct TYPE_8__ {scalar_t__ nFileSizeLow; scalar_t__ nFileSizeHigh; } ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_7__ {int TracksPerCylinder; int SectorsPerTrack; TYPE_1__ Cylinders; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ DISK_GEOMETRY ;
typedef  TYPE_3__ BY_HANDLE_FILE_INFORMATION ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileInformationByHandle (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_GEOMETRY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ is_device ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ valid_offset (int,int const) ; 

__attribute__((used)) static int
count_blocks (char *filename)
{
#ifdef _WIN32
	int fd;
	DISK_GEOMETRY geom;
	BY_HANDLE_FILE_INFORMATION hinfo;
	DWORD ret;
	loff_t len = 0;

	if ((fd = open(filename, O_RDONLY)) < 0) {
		perror(filename);
		exit(1);
	}
	/*
	 * This should probably use IOCTL_DISK_GET_LENGTH_INFO here, but
	 * this ioctl is only available in XP and up.
	 */
	if (is_device) {
		if (!DeviceIoControl((HANDLE)fd, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &geom, sizeof(geom), &ret, NULL)) {
			errno = GetLastError();
			die("unable to get length for '%s'");
		}
		len = geom.Cylinders.QuadPart*geom.TracksPerCylinder*geom.SectorsPerTrack*BLOCK_SIZE;
	} else {
		if (!GetFileInformationByHandle((HANDLE)fd, &hinfo)) {
				errno = GetLastError();
				die("unable to get length for '%s'");
		}
		len = ((loff_t)hinfo.nFileSizeHigh << 32) | (loff_t)hinfo.nFileSizeLow;
	}
	close(fd);
	return len/BLOCK_SIZE;
#else
  loff_t high, low;
  int fd;

  if ((fd = open (filename, O_RDONLY)) < 0)
    {
      perror (filename);
      exit (1);
    }
  low = 0;

  for (high = 1; valid_offset (fd, high); high *= 2)
    low = high;
  while (low < high - 1)
    {
      const loff_t mid = (low + high) / 2;

      if (valid_offset (fd, mid))
	low = mid;
      else
	high = mid;
    }
  valid_offset (fd, 0);
  close (fd);

  return (low + 1) / BLOCK_SIZE;
#endif
}