#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock_out; int /*<<< orphan*/ * p_buffers; } ;
typedef  TYPE_1__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

block_t * transcode_encoder_get_output_async( transcode_encoder_t *p_enc )
{
    vlc_mutex_lock( &p_enc->lock_out );
    block_t *p_data = p_enc->p_buffers;
    p_enc->p_buffers = NULL;
    vlc_mutex_unlock( &p_enc->lock_out );
    return p_data;
}