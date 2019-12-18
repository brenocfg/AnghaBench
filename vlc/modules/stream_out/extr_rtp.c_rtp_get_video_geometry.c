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
struct TYPE_4__ {int /*<<< orphan*/  fmtp; } ;
struct TYPE_5__ {TYPE_1__ rtp_fmt; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*) ; 

void rtp_get_video_geometry( sout_stream_id_sys_t *id, int *width, int *height )
{
    int ret = sscanf( id->rtp_fmt.fmtp, "%*s width=%d; height=%d; ", width, height );
    assert( ret == 2 );
}