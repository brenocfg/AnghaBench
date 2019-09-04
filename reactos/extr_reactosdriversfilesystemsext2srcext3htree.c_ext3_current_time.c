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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2LinuxTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 

__u32 ext3_current_time(struct inode *in)
{
    LARGE_INTEGER   SysTime;
    KeQuerySystemTime(&SysTime);

    return Ext2LinuxTime(SysTime);
}