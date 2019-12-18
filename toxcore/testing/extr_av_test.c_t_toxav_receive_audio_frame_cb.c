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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ frame ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_6__ {int /*<<< orphan*/  arb_mutex; int /*<<< orphan*/  arb; } ;
typedef  TYPE_2__ CallControl ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_write (int /*<<< orphan*/ ,TYPE_1__*) ; 

void t_toxav_receive_audio_frame_cb(ToxAV *av, uint32_t friend_number,
                                    int16_t const *pcm,
                                    size_t sample_count,
                                    uint8_t channels,
                                    uint32_t sampling_rate,
                                    void *user_data)
{
    CallControl *cc = user_data;
    frame *f = malloc(sizeof(uint16_t) + sample_count * sizeof(int16_t) * channels);
    memcpy(f->data, pcm, sample_count * sizeof(int16_t) * channels);
    f->size = sample_count;

    pthread_mutex_lock(cc->arb_mutex);
    free(rb_write(cc->arb, f));
    pthread_mutex_unlock(cc->arb_mutex);
}