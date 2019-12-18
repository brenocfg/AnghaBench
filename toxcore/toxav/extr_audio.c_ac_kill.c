#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  j_buf; int /*<<< orphan*/  decoder; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_1__ ACSession ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_DEBUG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  jbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_decoder_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_encoder_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 

void ac_kill(ACSession *ac)
{
    if (!ac)
        return;

    opus_encoder_destroy(ac->encoder);
    opus_decoder_destroy(ac->decoder);
    jbuf_free(ac->j_buf);

    pthread_mutex_destroy(ac->queue_mutex);

    LOGGER_DEBUG("Terminated audio handler: %p", ac);
    free(ac);
}