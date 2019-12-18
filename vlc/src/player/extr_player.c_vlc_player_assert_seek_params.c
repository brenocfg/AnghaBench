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
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;
typedef  enum vlc_player_seek_speed { ____Placeholder_vlc_player_seek_speed } vlc_player_seek_speed ;

/* Variables and functions */
 int VLC_PLAYER_SEEK_FAST ; 
 int VLC_PLAYER_SEEK_PRECISE ; 
 int VLC_PLAYER_WHENCE_ABSOLUTE ; 
 int VLC_PLAYER_WHENCE_RELATIVE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void
vlc_player_assert_seek_params(enum vlc_player_seek_speed speed,
                              enum vlc_player_whence whence)
{
    assert(speed == VLC_PLAYER_SEEK_PRECISE
        || speed == VLC_PLAYER_SEEK_FAST);
    assert(whence == VLC_PLAYER_WHENCE_ABSOLUTE
        || whence == VLC_PLAYER_WHENCE_RELATIVE);
    (void) speed; (void) whence;
}