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
struct TYPE_2__ {scalar_t__ size; } ;
struct vlc_player_input {int /*<<< orphan*/  thread; TYPE_1__ spu_track_vector; TYPE_1__ audio_track_vector; TYPE_1__ video_track_vector; TYPE_1__ program_vector; int /*<<< orphan*/ * teletext_menu; int /*<<< orphan*/ * titles; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct vlc_player_input*) ; 
 int /*<<< orphan*/  input_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vector_destroy (TYPE_1__*) ; 

void
vlc_player_input_Delete(struct vlc_player_input *input)
{
    assert(input->titles == NULL);
    assert(input->program_vector.size == 0);
    assert(input->video_track_vector.size == 0);
    assert(input->audio_track_vector.size == 0);
    assert(input->spu_track_vector.size == 0);
    assert(input->teletext_menu == NULL);

    vlc_vector_destroy(&input->program_vector);
    vlc_vector_destroy(&input->video_track_vector);
    vlc_vector_destroy(&input->audio_track_vector);
    vlc_vector_destroy(&input->spu_track_vector);

    input_Close(input->thread);
    free(input);
}