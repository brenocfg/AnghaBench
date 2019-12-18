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
typedef  int uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int BLOCKSZ ; 
 int /*<<< orphan*/  fillbuf (char*) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  rwc_pwrite (int,char*,int,int) ; 

__attribute__((used)) static void
random_writes(int fd, char *buf, uint64_t nblocks, int64_t n)
{
	for (int64_t i = 0; n == -1 || i < n; i++) {
		fillbuf(buf);
		rwc_pwrite(fd, buf, BLOCKSZ, (lrand48() % nblocks) * BLOCKSZ);
	}
}