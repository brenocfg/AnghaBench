#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {scalar_t__ cputype; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {unsigned int nfat_arch; } ;
typedef  TYPE_1__ Fat_header ;
typedef  TYPE_2__ Fat_arch ;

/* Variables and functions */
 scalar_t__ CPU_TYPE_POWERPC ; 

__attribute__((used)) static off_t
fat_find(Fat_header *fh) // *fh suffers bswap()
{
    Fat_arch *fa = (Fat_arch *)(1+ fh);
    //POWERPC NATIVE; do not need:  bswap(fh, sizeof(*fh) + (fh->nfat_arch>>24)*sizeof(*fa));
    unsigned j;
    for (j= 0; j < fh->nfat_arch; ++j, ++fa) {
        if (CPU_TYPE_POWERPC==fa->cputype) {
            return fa->offset;  // should not be 0 because of header
        }
    }
    return 0;
}