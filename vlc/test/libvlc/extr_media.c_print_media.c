#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_type; TYPE_3__* subtitle; TYPE_2__* video; TYPE_1__* audio; int /*<<< orphan*/  i_original_fourcc; int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_4__ libvlc_media_track_t ;
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  enum libvlc_meta_t { ____Placeholder_libvlc_meta_t } libvlc_meta_t ;
struct TYPE_9__ {char* psz_encoding; } ;
struct TYPE_8__ {int i_width; int i_height; int i_sar_num; int i_sar_den; int i_frame_rate_num; int i_frame_rate_den; } ;
struct TYPE_7__ {int i_channels; int i_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* libvlc_media_get_meta (int /*<<< orphan*/ *,int) ; 
 unsigned int libvlc_media_tracks_get (int /*<<< orphan*/ *,TYPE_4__***) ; 
 int /*<<< orphan*/  libvlc_media_tracks_release (TYPE_4__**,unsigned int) ; 
 int libvlc_meta_DiscTotal ; 
 int libvlc_meta_Title ; 
#define  libvlc_track_audio 131 
#define  libvlc_track_text 130 
#define  libvlc_track_unknown 129 
#define  libvlc_track_video 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  test_log (char*,...) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void print_media(libvlc_media_t *media)
{
    libvlc_media_track_t **pp_tracks;
    unsigned i_count = libvlc_media_tracks_get(media, &pp_tracks);
    if (i_count > 0)
    {
        for (unsigned i = 0; i < i_count; ++i)
        {
            libvlc_media_track_t *p_track = pp_tracks[i];
            test_log("\ttrack(%d/%d): codec: %4.4s/%4.4s, ", i, p_track->i_id,
                (const char *)&p_track->i_codec,
                (const char *)&p_track->i_original_fourcc);
            switch (p_track->i_type)
            {
            case libvlc_track_audio:
                printf("audio: channels: %u, rate: %u\n",
                       p_track->audio->i_channels, p_track->audio->i_rate);
                break;
            case libvlc_track_video:
                printf("video: %ux%u, sar: %u/%u, fps: %u/%u\n",
                       p_track->video->i_width, p_track->video->i_height,
                       p_track->video->i_sar_num, p_track->video->i_sar_den,
                       p_track->video->i_frame_rate_num, p_track->video->i_frame_rate_den);
                break;
            case libvlc_track_text:
                printf("text: %s\n", p_track->subtitle->psz_encoding);
                break;
            case libvlc_track_unknown:
                printf("unknown\n");
                break;
            default:
                vlc_assert_unreachable();
            }
        }
        libvlc_media_tracks_release(pp_tracks, i_count);
    }
    else
        test_log("\tmedia doesn't have any tracks\n");

    for (enum libvlc_meta_t i = libvlc_meta_Title;
         i <= libvlc_meta_DiscTotal; ++i)
    {
        char *psz_meta = libvlc_media_get_meta(media, i);
        if (psz_meta != NULL)
            test_log("\tmeta(%d): '%s'\n", i, psz_meta);
        free(psz_meta);
    }
}