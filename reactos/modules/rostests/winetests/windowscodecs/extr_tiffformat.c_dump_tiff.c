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
struct tiff_1bpp_data {int dir_offset; } ;
struct IFD_entry {int id; int type; int count; int value; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void dump_tiff(void *buf)
{
    UINT count, i;
    struct tiff_1bpp_data *tiff;
    struct IFD_entry *tag;

    tiff = buf;
    count = *(short *)((char *)tiff + tiff->dir_offset);
    tag = (struct IFD_entry *)((char *)tiff + tiff->dir_offset + sizeof(short));

    for (i = 0; i < count; i++)
    {
        printf("tag %u: id %04x, type %04x, count %u, value %d",
                i, tag[i].id, tag[i].type, tag[i].count, tag[i].value);
        if (tag[i].id == 0x102 && tag[i].count > 2)
        {
            short *bps = (short *)((char *)tiff + tag[i].value);
            printf(" (%d,%d,%d,%d)\n", bps[0], bps[1], bps[2], bps[3]);
        }
        else
            printf("\n");
    }
}