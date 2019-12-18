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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,uintptr_t*,int) ; 

__attribute__((used)) static uintptr_t mmap_probe_seed(void)
{
  uintptr_t val;
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd != -1) {
    int ok = ((size_t)read(fd, &val, sizeof(val)) == sizeof(val));
    (void)close(fd);
    if (ok) return val;
  }
  return 1;  /* Punt. */
}