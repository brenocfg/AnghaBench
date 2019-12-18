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
struct vtoc {int dummy; } ;
typedef  struct vtoc extvtoc ;

/* Variables and functions */
 int /*<<< orphan*/  DKIOCGEXTVTOC ; 
 int /*<<< orphan*/  DKIOCGVTOC ; 
 int ENOSYS ; 
 scalar_t__ ENOTSUP ; 
 scalar_t__ ENOTTY ; 
 scalar_t__ errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct vtoc*) ; 

int
efi_type(int fd)
{
#if 0
	struct vtoc vtoc;
	struct extvtoc extvtoc;

	if (ioctl(fd, DKIOCGEXTVTOC, &extvtoc) == -1) {
		if (errno == ENOTSUP)
			return (1);
		else if (errno == ENOTTY) {
			if (ioctl(fd, DKIOCGVTOC, &vtoc) == -1)
				if (errno == ENOTSUP)
					return (1);
		}
	}
	return (0);
#else
	return (ENOSYS);
#endif
}