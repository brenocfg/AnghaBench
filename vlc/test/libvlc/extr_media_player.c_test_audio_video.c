#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
struct TYPE_4__ {int /*<<< orphan*/  psz_device; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ libvlc_audio_output_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* libvlc_audio_output_device_enum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_audio_output_device_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_audio_output_device_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int libvlc_get_fullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_set_fullscreen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  libvlc_toggle_fullscreen (int /*<<< orphan*/ *) ; 
 int libvlc_video_get_scale (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_video_set_scale (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_audio_video(libvlc_media_player_t *mp)
{
    bool fs = libvlc_get_fullscreen(mp);
    libvlc_set_fullscreen(mp, true);
    assert(libvlc_get_fullscreen(mp));
    libvlc_set_fullscreen(mp, false);
    assert(!libvlc_get_fullscreen(mp));
    libvlc_toggle_fullscreen(mp);
    assert(libvlc_get_fullscreen(mp));
    libvlc_toggle_fullscreen(mp);
    assert(!libvlc_get_fullscreen(mp));
    libvlc_set_fullscreen(mp, fs);
    assert(libvlc_get_fullscreen(mp) == fs);

    assert(libvlc_video_get_scale(mp) == 0.); /* default */
    libvlc_video_set_scale(mp, 0.); /* no-op */
    libvlc_video_set_scale(mp, 2.5);
    assert(libvlc_video_get_scale(mp) == 2.5);
    libvlc_video_set_scale(mp, 0.);
    libvlc_video_set_scale(mp, 0.); /* no-op */
    assert(libvlc_video_get_scale(mp) == 0.);

    libvlc_audio_output_device_t *aouts = libvlc_audio_output_device_enum(mp);
    for (libvlc_audio_output_device_t *e = aouts; e != NULL; e = e->p_next)
    {
        libvlc_audio_output_device_set( mp, NULL, e->psz_device );
    }
    libvlc_audio_output_device_list_release( aouts );
}