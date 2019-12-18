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
struct vlc_h2_output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int counter ; 
 int expect_hello ; 
 int /*<<< orphan*/  fake_tls ; 
 int /*<<< orphan*/ * frame (unsigned char) ; 
 int /*<<< orphan*/ * frame_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx ; 
 int send_failure ; 
 struct vlc_h2_output* vlc_h2_output_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_h2_output_destroy (struct vlc_h2_output*) ; 
 int vlc_h2_output_send (struct vlc_h2_output*,int /*<<< orphan*/ *) ; 
 int vlc_h2_output_send_prio (struct vlc_h2_output*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

int main(void)
{
    struct vlc_h2_output *out;

    /* Dummy */
    out = vlc_h2_output_create(&fake_tls, false);
    assert(out != NULL);
    vlc_h2_output_destroy(out);

    vlc_sem_init(&rx, 0);
    out = vlc_h2_output_create(&fake_tls, expect_hello = true);
    assert(out != NULL);
    vlc_h2_output_destroy(out);
    vlc_sem_destroy(&rx);

    /* Success */
    vlc_sem_init(&rx, 0);
    out = vlc_h2_output_create(&fake_tls, false);
    assert(out != NULL);
    assert(vlc_h2_output_send_prio(out, NULL) == -1);
    assert(vlc_h2_output_send_prio(out, frame(0)) == 0);
    assert(vlc_h2_output_send_prio(out, frame(1)) == 0);
    assert(vlc_h2_output_send(out, NULL) == -1);
    assert(vlc_h2_output_send(out, frame(2)) == 0);
    assert(vlc_h2_output_send(out, frame(3)) == 0);
    assert(vlc_h2_output_send(out, frame_list(frame(4), frame(5),
                                              frame(6), NULL)) == 0);
    assert(vlc_h2_output_send(out, frame(7)) == 0);
    for (unsigned i = 0; i < 8; i++)
        vlc_sem_wait(&rx);

    assert(vlc_h2_output_send_prio(out, frame(8)) == 0);
    assert(vlc_h2_output_send(out, frame(9)) == 0);

    vlc_h2_output_destroy(out);
    vlc_sem_destroy(&rx);

    /* Failure */
    send_failure = true;

    vlc_sem_init(&rx, 0);
    counter = 10;
    out = vlc_h2_output_create(&fake_tls, false);
    assert(out != NULL);

    assert(vlc_h2_output_send(out, frame(10)) == 0);
    for (unsigned char i = 11; vlc_h2_output_send(out, frame(i)) == 0; i++)
        vlc_tick_sleep(VLC_TICK_FROM_MS(100)); /* eventually, it should start failing */
    assert(vlc_h2_output_send(out, frame(0)) == -1);
    assert(vlc_h2_output_send_prio(out, frame(0)) == -1);
    vlc_h2_output_destroy(out);
    vlc_sem_destroy(&rx);

    /* Failure during hello */
    vlc_sem_init(&rx, 0);
    counter = 0;
    out = vlc_h2_output_create(&fake_tls, expect_hello = true);
    assert(out != NULL);
    vlc_sem_wait(&rx);

    for (unsigned char i = 1; vlc_h2_output_send_prio(out, frame(i)) == 0; i++)
        vlc_tick_sleep(VLC_TICK_FROM_MS(100));
    assert(vlc_h2_output_send(out, frame(0)) == -1);
    assert(vlc_h2_output_send_prio(out, frame(0)) == -1);
    vlc_h2_output_destroy(out);
    vlc_sem_destroy(&rx);

    return 0;
}