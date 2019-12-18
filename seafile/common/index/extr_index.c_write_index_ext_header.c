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
typedef  int /*<<< orphan*/  WriteIndexInfo ;

/* Variables and functions */
 scalar_t__ ce_write (int /*<<< orphan*/ *,int,unsigned int*,int) ; 
 unsigned int htonl (unsigned int) ; 

__attribute__((used)) static int write_index_ext_header(WriteIndexInfo *info, int fd,
                                  unsigned int ext, unsigned int sz)
{
    ext = htonl(ext);
    sz = htonl(sz);
    return ((ce_write(info, fd, &ext, 4) < 0) ||
            (ce_write(info, fd, &sz, 4) < 0)) ? -1 : 0;
}