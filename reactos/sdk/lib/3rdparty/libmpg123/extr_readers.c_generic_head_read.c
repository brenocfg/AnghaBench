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
struct TYPE_6__ {TYPE_1__* rd; } ;
typedef  TYPE_2__ mpg123_handle ;
struct TYPE_5__ {int (* fullread ) (TYPE_2__*,unsigned char*,int) ;} ;

/* Variables and functions */
 int FALSE ; 
 int READER_MORE ; 
 int TRUE ; 
 int stub1 (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static int generic_head_read(mpg123_handle *fr,unsigned long *newhead)
{
	unsigned char hbuf[4];
	int ret = fr->rd->fullread(fr,hbuf,4);
	if(ret == READER_MORE) return ret;
	if(ret != 4) return FALSE;

	*newhead = ((unsigned long) hbuf[0] << 24) |
	           ((unsigned long) hbuf[1] << 16) |
	           ((unsigned long) hbuf[2] << 8)  |
	            (unsigned long) hbuf[3];

	return TRUE;
}