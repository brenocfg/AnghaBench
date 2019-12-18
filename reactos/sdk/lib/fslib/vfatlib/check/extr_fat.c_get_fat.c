#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ data_clusters; int fat_bits; } ;
struct TYPE_5__ {int value; scalar_t__ reserved; } ;
typedef  TYPE_1__ FAT_ENTRY ;
typedef  TYPE_2__ DOS_FS ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int,...) ; 
 int le16toh (unsigned short) ; 
 scalar_t__ le32toh (unsigned int) ; 

void get_fat(FAT_ENTRY * entry, void *fat, uint32_t cluster, DOS_FS * fs)
{
    unsigned char *ptr;

    if (cluster > fs->data_clusters + 1) {
	die("Internal error: cluster out of range in get_fat() (%lu > %lu).",
		(unsigned long)cluster, (unsigned long)(fs->data_clusters + 1));
    }

    switch (fs->fat_bits) {
    case 12:
	ptr = &((unsigned char *)fat)[cluster * 3 / 2];
	entry->value = 0xfff & (cluster & 1 ? (ptr[0] >> 4) | (ptr[1] << 4) :
				(ptr[0] | ptr[1] << 8));
	break;
    case 16:
	entry->value = le16toh(((unsigned short *)fat)[cluster]);
	break;
    case 32:
	/* According to M$, the high 4 bits of a FAT32 entry are reserved and
	 * are not part of the cluster number. So we cut them off. */
	{
	    uint32_t e = le32toh(((unsigned int *)fat)[cluster]);
	    entry->value = e & 0xfffffff;
	    entry->reserved = e >> 28;
	}
	break;
    default:
	die("Bad FAT entry size: %d bits.", fs->fat_bits);
    }
}