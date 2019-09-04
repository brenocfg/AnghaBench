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
struct TYPE_5__ {long (* fullread ) (TYPE_2__*,unsigned char*,int) ;} ;

/* Variables and functions */
 int READER_MORE ; 
 long stub1 (TYPE_2__*,unsigned char*,int) ; 

__attribute__((used)) static int generic_read_frame_body(mpg123_handle *fr,unsigned char *buf, int size)
{
	long l;

	if((l=fr->rd->fullread(fr,buf,size)) != size)
	{
		long ll = l;
		if(ll <= 0) ll = 0;
		return READER_MORE;
	}
	return l;
}