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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  bb_copyfd_exact_size (int,int,scalar_t__) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unzip_skip(int zip_fd, off_t skip)
{
	if (skip != 0)
		if (lseek(zip_fd, skip, SEEK_CUR) == (off_t)-1)
			bb_copyfd_exact_size(zip_fd, -1, skip);
}