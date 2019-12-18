#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_6__ {int const i_frame_length; int const i_bytes_per_frame; int /*<<< orphan*/  i_rate; } ;
struct TYPE_7__ {TYPE_1__ audio; } ;
struct mock_track {TYPE_2__ fmt; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 TYPE_3__* block_Alloc (int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int samples_from_vlc_tick (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *
CreateAudioBlock(demux_t *demux, struct mock_track *track, vlc_tick_t length)
{
    const int64_t samples =
        samples_from_vlc_tick(length, track->fmt.audio.i_rate);
    const int64_t bytes = samples / track->fmt.audio.i_frame_length
                        * track->fmt.audio.i_bytes_per_frame;
    block_t *b = block_Alloc(bytes);
    if (!b)
        return NULL;
    memset(b->p_buffer, 0, b->i_buffer);
    return b;
    (void) demux;
}