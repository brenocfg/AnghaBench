#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_btrt; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_avg_bitrate; int /*<<< orphan*/  i_max_bitrate; int /*<<< orphan*/  i_buffer_size; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_btrt_t ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int i_read ; 

__attribute__((used)) static int MP4_ReadBox_btrt( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_READBOX_ENTER( MP4_Box_data_btrt_t, NULL );

    if(i_read != 12)
        MP4_READBOX_EXIT( 0 );

    MP4_GET4BYTES( p_box->data.p_btrt->i_buffer_size );
    MP4_GET4BYTES( p_box->data.p_btrt->i_max_bitrate );
    MP4_GET4BYTES( p_box->data.p_btrt->i_avg_bitrate );

    MP4_READBOX_EXIT( 1 );
}