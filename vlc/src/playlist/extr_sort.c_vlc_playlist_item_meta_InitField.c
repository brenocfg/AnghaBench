#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vlc_playlist_item_meta {int has_date; int has_track_number; int has_disc_number; int has_rating; void* rating; int /*<<< orphan*/  url; void* disc_number; void* track_number; void* date; int /*<<< orphan*/  genre; int /*<<< orphan*/  album_artist; int /*<<< orphan*/  album; int /*<<< orphan*/  artist; int /*<<< orphan*/  duration; int /*<<< orphan*/  title_or_name; TYPE_1__* item; } ;
struct TYPE_5__ {char* psz_name; int /*<<< orphan*/  i_duration; } ;
typedef  TYPE_2__ input_item_t ;
typedef  enum vlc_playlist_sort_key { ____Placeholder_vlc_playlist_sort_key } vlc_playlist_sort_key ;
struct TYPE_4__ {TYPE_2__* media; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_STR (char const*) ; 
 int /*<<< orphan*/  INPUT_DURATION_INDEFINITE ; 
 int /*<<< orphan*/  INPUT_DURATION_UNSET ; 
#define  VLC_PLAYLIST_SORT_KEY_ALBUM 138 
#define  VLC_PLAYLIST_SORT_KEY_ALBUM_ARTIST 137 
#define  VLC_PLAYLIST_SORT_KEY_ARTIST 136 
#define  VLC_PLAYLIST_SORT_KEY_DATE 135 
#define  VLC_PLAYLIST_SORT_KEY_DISC_NUMBER 134 
#define  VLC_PLAYLIST_SORT_KEY_DURATION 133 
#define  VLC_PLAYLIST_SORT_KEY_GENRE 132 
#define  VLC_PLAYLIST_SORT_KEY_RATING 131 
#define  VLC_PLAYLIST_SORT_KEY_TITLE 130 
#define  VLC_PLAYLIST_SORT_KEY_TRACK_NUMBER 129 
#define  VLC_PLAYLIST_SORT_KEY_URL 128 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* atoll (char const*) ; 
 char* input_item_GetMetaLocked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_meta_Album ; 
 int /*<<< orphan*/  vlc_meta_AlbumArtist ; 
 int /*<<< orphan*/  vlc_meta_Artist ; 
 int /*<<< orphan*/  vlc_meta_Date ; 
 int /*<<< orphan*/  vlc_meta_DiscNumber ; 
 int /*<<< orphan*/  vlc_meta_Genre ; 
 int /*<<< orphan*/  vlc_meta_Rating ; 
 int /*<<< orphan*/  vlc_meta_Title ; 
 int /*<<< orphan*/  vlc_meta_TrackNumber ; 
 int /*<<< orphan*/  vlc_meta_URL ; 
 int vlc_playlist_item_meta_CopyString (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
vlc_playlist_item_meta_InitField(struct vlc_playlist_item_meta *meta,
                                 enum vlc_playlist_sort_key key)
{
    input_item_t *media = meta->item->media;
    switch (key)
    {
        case VLC_PLAYLIST_SORT_KEY_TITLE:
        {
            const char *value = input_item_GetMetaLocked(media, vlc_meta_Title);
            if (EMPTY_STR(value))
                value = media->psz_name;
            return vlc_playlist_item_meta_CopyString(&meta->title_or_name,
                                                     value);
        }
        case VLC_PLAYLIST_SORT_KEY_DURATION:
        {
            if (media->i_duration == INPUT_DURATION_INDEFINITE
             || media->i_duration == INPUT_DURATION_UNSET)
                meta->duration = 0;
            else
                meta->duration = media->i_duration;
            return VLC_SUCCESS;
        }
        case VLC_PLAYLIST_SORT_KEY_ARTIST:
        {
            const char *value = input_item_GetMetaLocked(media,
                                                         vlc_meta_Artist);
            return vlc_playlist_item_meta_CopyString(&meta->artist, value);
        }
        case VLC_PLAYLIST_SORT_KEY_ALBUM:
        {
            const char *value = input_item_GetMetaLocked(media, vlc_meta_Album);
            return vlc_playlist_item_meta_CopyString(&meta->album, value);
        }
        case VLC_PLAYLIST_SORT_KEY_ALBUM_ARTIST:
        {
            const char *value = input_item_GetMetaLocked(media,
                                                         vlc_meta_AlbumArtist);
            return vlc_playlist_item_meta_CopyString(&meta->album_artist,
                                                     value);
        }
        case VLC_PLAYLIST_SORT_KEY_GENRE:
        {
            const char *value = input_item_GetMetaLocked(media, vlc_meta_Genre);
            return vlc_playlist_item_meta_CopyString(&meta->genre, value);
        }
        case VLC_PLAYLIST_SORT_KEY_DATE:
        {
            const char *str = input_item_GetMetaLocked(media, vlc_meta_Date);
            meta->has_date = !EMPTY_STR(str);
            if (meta->has_date)
                meta->date = atoll(str);
            return VLC_SUCCESS;
        }
        case VLC_PLAYLIST_SORT_KEY_TRACK_NUMBER:
        {
            const char *str = input_item_GetMetaLocked(media,
                                                       vlc_meta_TrackNumber);
            meta->has_track_number = !EMPTY_STR(str);
            if (meta->has_track_number)
                meta->track_number = atoll(str);
            return VLC_SUCCESS;
        }
        case VLC_PLAYLIST_SORT_KEY_DISC_NUMBER:
        {
            const char *str = input_item_GetMetaLocked(media,
                                                       vlc_meta_DiscNumber);
            meta->has_disc_number = !EMPTY_STR(str);
            if (meta->has_disc_number)
                meta->disc_number = atoll(str);
            return VLC_SUCCESS;
        }
        case VLC_PLAYLIST_SORT_KEY_URL:
        {
            const char *value = input_item_GetMetaLocked(media, vlc_meta_URL);
            return vlc_playlist_item_meta_CopyString(&meta->url, value);
        }
        case VLC_PLAYLIST_SORT_KEY_RATING:
        {
            const char *str = input_item_GetMetaLocked(media, vlc_meta_Rating);
            meta->has_rating = !EMPTY_STR(str);
            if (meta->has_rating)
                meta->rating = atoll(str);
            return VLC_SUCCESS;
        }
        default:
            assert(!"Unknown sort key");
            vlc_assert_unreachable();
    }
}