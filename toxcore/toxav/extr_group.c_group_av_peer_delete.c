#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buffer; scalar_t__ audio_decoder; } ;
typedef  TYPE_1__ Group_Peer_AV ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  opus_decoder_destroy (scalar_t__) ; 
 int /*<<< orphan*/  terminate_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void group_av_peer_delete(void *object, int groupnumber, int friendgroupnumber, void *peer_object)
{
    Group_Peer_AV *peer_av = peer_object;

    if (!peer_av)
        return;

    if (peer_av->audio_decoder)
        opus_decoder_destroy(peer_av->audio_decoder);

    terminate_queue(peer_av->buffer);
    free(peer_object);
}