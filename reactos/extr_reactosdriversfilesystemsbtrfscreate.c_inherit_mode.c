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
struct TYPE_4__ {int st_mode; } ;
struct TYPE_5__ {TYPE_1__ inode_item; } ;
typedef  TYPE_2__ fcb ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_ISVTX ; 

UINT32 inherit_mode(fcb* parfcb, BOOL is_dir) {
    UINT32 mode;

    if (!parfcb)
        return 0755;

    mode = parfcb->inode_item.st_mode & ~S_IFDIR;
    mode &= ~S_ISVTX; // clear sticky bit
    mode &= ~S_ISUID; // clear setuid bit

    if (!is_dir)
        mode &= ~S_ISGID; // if not directory, clear setgid bit

    return mode;
}