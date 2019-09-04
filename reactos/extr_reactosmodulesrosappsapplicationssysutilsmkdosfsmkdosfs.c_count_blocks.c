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
typedef  int loff_t ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
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