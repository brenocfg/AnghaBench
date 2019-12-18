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
struct vlc_playlist_item_meta {int /*<<< orphan*/  rating; int /*<<< orphan*/  has_rating; int /*<<< orphan*/  url; int /*<<< orphan*/  disc_number; int /*<<< orphan*/  has_disc_number; int /*<<< orphan*/  track_number; int /*<<< orphan*/  has_track_number; int /*<<< orphan*/  date; int /*<<< orphan*/  has_date; int /*<<< orphan*/  genre; int /*<<< orphan*/  album_artist; int /*<<< orphan*/  album; int /*<<< orphan*/  artist; int /*<<< orphan*/  duration; int /*<<< orphan*/  title_or_name; } ;
typedef  enum vlc_playlist_sort_key { ____Placeholder_vlc_playlist_sort_key } vlc_playlist_sort_key ;

/* Variables and functions */
 int CompareIntegers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CompareOptionalIntegers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CompareStrings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static inline int
CompareMetaByKey(const struct vlc_playlist_item_meta *a,
                 const struct vlc_playlist_item_meta *b,
                 enum vlc_playlist_sort_key key)
{
    switch (key)
    {
        case VLC_PLAYLIST_SORT_KEY_TITLE:
            return CompareStrings(a->title_or_name, b->title_or_name);
        case VLC_PLAYLIST_SORT_KEY_DURATION:
            return CompareIntegers(a->duration, b->duration);
        case VLC_PLAYLIST_SORT_KEY_ARTIST:
            return CompareStrings(a->artist, b->artist);
        case VLC_PLAYLIST_SORT_KEY_ALBUM:
            return CompareStrings(a->album, b->album);
        case VLC_PLAYLIST_SORT_KEY_ALBUM_ARTIST:
            return CompareStrings(a->album_artist, b->album_artist);
        case VLC_PLAYLIST_SORT_KEY_GENRE:
            return CompareStrings(a->genre, b->genre);
        case VLC_PLAYLIST_SORT_KEY_DATE:
            return CompareOptionalIntegers(a->has_date, a->date,
                                           b->has_date, b->date);
        case VLC_PLAYLIST_SORT_KEY_TRACK_NUMBER:
            return CompareOptionalIntegers(a->has_track_number, a->track_number,
                                           b->has_track_number, b->track_number);
        case VLC_PLAYLIST_SORT_KEY_DISC_NUMBER:
            return CompareOptionalIntegers(a->has_disc_number, a->disc_number,
                                           b->has_disc_number, b->disc_number);
        case VLC_PLAYLIST_SORT_KEY_URL:
            return CompareStrings(a->url, b->url);
        case VLC_PLAYLIST_SORT_KEY_RATING:
            return CompareOptionalIntegers(a->has_rating, a->rating,
                                           b->has_rating, b->rating);
        default:
            assert(!"Unknown sort key");
            vlc_assert_unreachable();
     }
}