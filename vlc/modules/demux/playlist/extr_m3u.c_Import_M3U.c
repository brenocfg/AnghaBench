#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ force; } ;
struct TYPE_7__ {char* (* p_sys ) (char const*) ;int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_readdir; int /*<<< orphan*/  s; TYPE_1__ obj; } ;
typedef  TYPE_2__ stream_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FILE (TYPE_2__*) ; 
 char* CheckUnicode (char const*) ; 
 scalar_t__ ContainsURL (int /*<<< orphan*/  const*,int) ; 
 char* GuessEncoding (char const*) ; 
 int /*<<< orphan*/  IsHLS (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ReadDir ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  access_vaDirectoryControlHelper ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 scalar_t__ stream_HasExtension (TYPE_2__*,char*) ; 
 char* stream_MimeType (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 scalar_t__ vlc_ascii_strcasecmp (char*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int) ; 

int Import_M3U( vlc_object_t *p_this )
{
    stream_t *p_stream = (stream_t *)p_this;
    const uint8_t *p_peek;
    ssize_t i_peek;
    int offset = 0;

    CHECK_FILE(p_stream);
    i_peek = vlc_stream_Peek( p_stream->s, &p_peek, 1024 );
    if( i_peek < 8 )
        return VLC_EGENERIC;

    /* Encoding: UTF-8 or unspecified */
    char *(*pf_dup) (const char *) = GuessEncoding;

    if (stream_HasExtension(p_stream, ".m3u8")
     || strncasecmp((const char *)p_peek, "RTSPtext", 8) == 0) /* QuickTime */
        pf_dup = CheckUnicode;
    else
    if (memcmp( p_peek, "\xef\xbb\xbf", 3) == 0) /* UTF-8 Byte Order Mark */
    {
        if( i_peek < 12 )
            return VLC_EGENERIC;
        pf_dup = CheckUnicode;
        offset = 3;
        p_peek += offset;
        i_peek -= offset;
    }

    /* File type: playlist, or not (HLS manifest or whatever else) */
    char *type = stream_MimeType(p_stream->s);
    bool match;

    if (p_stream->obj.force)
        match = true;
    else
    if (type != NULL
     && !vlc_ascii_strcasecmp(type, "application/vnd.apple.mpegurl")) /* HLS */
        match = false;
    else
    if (memcmp(p_peek, "#EXTM3U", 7 ) == 0
     || (type != NULL
      && (vlc_ascii_strcasecmp(type, "application/mpegurl") == 0
       || vlc_ascii_strcasecmp(type, "application/x-mpegurl") == 0
       || vlc_ascii_strcasecmp(type, "audio/mpegurl") == 0
       || vlc_ascii_strcasecmp(type, "vnd.apple.mpegURL") == 0
       || vlc_ascii_strcasecmp(type, "audio/x-mpegurl") == 0))
     || stream_HasExtension(p_stream, ".m3u8")
     || stream_HasExtension(p_stream, ".m3u"))
        match = !IsHLS(p_peek, i_peek);
    else
    if (stream_HasExtension(p_stream, ".vlc")
     || strncasecmp((const char *)p_peek, "RTSPtext", 8) == 0
     || ContainsURL(p_peek, i_peek))
        match = true;
    else
        match = false;

    free(type);

    if (!match)
        return VLC_EGENERIC;

    if (offset != 0 && vlc_stream_Seek(p_stream->s, offset))
        return VLC_EGENERIC;

    msg_Dbg( p_stream, "found valid M3U playlist" );
    p_stream->p_sys = pf_dup;
    p_stream->pf_readdir = ReadDir;
    p_stream->pf_control = access_vaDirectoryControlHelper;

    return VLC_SUCCESS;
}