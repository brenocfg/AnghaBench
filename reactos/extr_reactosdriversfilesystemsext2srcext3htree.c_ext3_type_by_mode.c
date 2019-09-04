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
typedef  int umode_t ;

/* Variables and functions */
 unsigned char EXT3_FT_BLKDEV ; 
 unsigned char EXT3_FT_CHRDEV ; 
 unsigned char EXT3_FT_DIR ; 
 unsigned char EXT3_FT_FIFO ; 
 unsigned char EXT3_FT_REG_FILE ; 
 unsigned char EXT3_FT_SOCK ; 
 unsigned char EXT3_FT_SYMLINK ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 

unsigned char ext3_type_by_mode(umode_t mode)
{
    unsigned char type = 0;

    switch (mode & S_IFMT) {
    case S_IFREG:
        type = EXT3_FT_REG_FILE;
        break;
    case S_IFDIR:
        type = EXT3_FT_DIR;
        break;
    case S_IFCHR:
        type =  EXT3_FT_CHRDEV;
        break;
    case S_IFBLK:
        type = EXT3_FT_BLKDEV;
        break;
    case S_IFIFO:
        type = EXT3_FT_FIFO;
        break;
    case S_IFSOCK:
        type = EXT3_FT_SOCK;
        break;
    case S_IFLNK:
        type = EXT3_FT_SYMLINK;
    }

    return type;
}