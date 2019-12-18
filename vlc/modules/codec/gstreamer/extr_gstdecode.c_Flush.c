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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_6__ {int b_prerolled; int /*<<< orphan*/  p_que; int /*<<< orphan*/  p_decoder; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  GstBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  GST_FORMAT_BYTES ; 
 int /*<<< orphan*/  GST_SEEK_FLAG_FLUSH ; 
 int /*<<< orphan*/ * gst_atomic_queue_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gst_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gst_element_seek_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Flush( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    GstBuffer *p_buffer;
    gboolean b_ret;

    /* Send a new segment event. Seeking position is
     * irrelevant in this case, as the main motive for a
     * seek here, is to tell the elements to start flushing
     * and start accepting buffers from a new time segment */
    b_ret = gst_element_seek_simple( p_sys->p_decoder,
            GST_FORMAT_BYTES, GST_SEEK_FLAG_FLUSH, 0 );
    msg_Dbg( p_dec, "new segment event : %d", b_ret );

    /* flush the output buffers from the queue */
    while( ( p_buffer = gst_atomic_queue_pop( p_sys->p_que ) ) )
        gst_buffer_unref( p_buffer );

    p_sys->b_prerolled = false;
}