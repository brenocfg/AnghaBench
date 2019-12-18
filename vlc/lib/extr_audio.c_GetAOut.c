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
struct TYPE_3__ {int /*<<< orphan*/  player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static audio_output_t *GetAOut( libvlc_media_player_t *mp )
{
    assert( mp != NULL );

    audio_output_t *p_aout = vlc_player_aout_Hold(mp->player);
    if( p_aout == NULL )
        libvlc_printerr( "No active audio output" );
    return p_aout;
}