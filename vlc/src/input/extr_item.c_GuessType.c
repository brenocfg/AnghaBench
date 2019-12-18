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
typedef  int /*<<< orphan*/  tab ;
struct item_type_entry {char* member_0; int const member_1; int member_2; int b_net; int i_type; int /*<<< orphan*/  psz_scheme; } ;
struct TYPE_3__ {int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_1__ input_item_t ;
typedef  enum input_item_type_e { ____Placeholder_input_item_type_e } input_item_type_e ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct item_type_entry const*) ; 
#define  ITEM_TYPE_CARD 134 
#define  ITEM_TYPE_DIRECTORY 133 
#define  ITEM_TYPE_DISC 132 
#define  ITEM_TYPE_FILE 131 
#define  ITEM_TYPE_PLAYLIST 130 
#define  ITEM_TYPE_STREAM 129 
#define  ITEM_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  assert (int) ; 
 struct item_type_entry* bsearch (int /*<<< orphan*/ ,struct item_type_entry const*,size_t,int,scalar_t__ (*) (int /*<<< orphan*/ ,struct item_type_entry const*)) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ typecmp (int /*<<< orphan*/ ,struct item_type_entry const*) ; 

__attribute__((used)) static enum input_item_type_e GuessType( const input_item_t *p_item, bool *p_net )
{
    static const struct item_type_entry tab[] =
    {   /* /!\ Alphabetical order /!\ */
        /* Short match work, not just exact match */
        { "alsa",   ITEM_TYPE_CARD, false },
        { "atsc",   ITEM_TYPE_CARD, false },
        { "bd",     ITEM_TYPE_DISC, false },
        { "bluray", ITEM_TYPE_DISC, false },
        { "cable",  ITEM_TYPE_CARD, false },
        { "cdda",   ITEM_TYPE_DISC, false },
        { "cqam",   ITEM_TYPE_CARD, false },
        { "dc1394", ITEM_TYPE_CARD, false },
        { "dccp",   ITEM_TYPE_STREAM, true },
        { "deckli", ITEM_TYPE_CARD, false }, /* decklink */
        { "dir",    ITEM_TYPE_DIRECTORY, false },
        { "dshow",  ITEM_TYPE_CARD, false },
        { "dtv",    ITEM_TYPE_CARD, false },
        { "dvb",    ITEM_TYPE_CARD, false },
        { "dvd",    ITEM_TYPE_DISC, false },
        { "eyetv",  ITEM_TYPE_CARD, false },
        { "fd",     ITEM_TYPE_UNKNOWN, false },
        { "file",   ITEM_TYPE_FILE, false },
        { "ftp",    ITEM_TYPE_FILE, true },
        { "http",   ITEM_TYPE_FILE, true },
        { "icyx",   ITEM_TYPE_STREAM, true },
        { "imem",   ITEM_TYPE_UNKNOWN, false },
        { "isdb-",  ITEM_TYPE_CARD, false },
        { "itpc",   ITEM_TYPE_PLAYLIST, true },
        { "jack",   ITEM_TYPE_CARD, false },
        { "linsys", ITEM_TYPE_CARD, false },
        { "live",   ITEM_TYPE_STREAM, true }, /* livedotcom */
        { "mms",    ITEM_TYPE_STREAM, true },
        { "mtp",    ITEM_TYPE_DISC, false },
        { "nfs",    ITEM_TYPE_FILE, true },
        { "ofdm",   ITEM_TYPE_CARD, false },
        { "oss",    ITEM_TYPE_CARD, false },
        { "pnm",    ITEM_TYPE_STREAM, true },
        { "pulse",  ITEM_TYPE_CARD, false },
        { "qam",    ITEM_TYPE_CARD, false },
        { "qpsk",   ITEM_TYPE_CARD, false },
        { "qtcapt", ITEM_TYPE_CARD, false }, /* qtcapture */
        { "qtsound",ITEM_TYPE_CARD, false },
        { "raw139", ITEM_TYPE_CARD, false }, /* raw1394 */
        { "rt",     ITEM_TYPE_STREAM, true }, /* rtp, rtsp, rtmp */
        { "satell", ITEM_TYPE_CARD, false }, /* satellite */
        { "satip",  ITEM_TYPE_STREAM, true }, /* satellite over ip */
        { "screen", ITEM_TYPE_CARD, false },
        { "sdp",    ITEM_TYPE_STREAM, true },
        { "sftp",   ITEM_TYPE_FILE, true },
        { "shm",    ITEM_TYPE_CARD, false },
        { "smb",    ITEM_TYPE_FILE, true },
        { "stream", ITEM_TYPE_STREAM, false },
        { "svcd",   ITEM_TYPE_DISC, false },
        { "tcp",    ITEM_TYPE_STREAM, true },
        { "terres", ITEM_TYPE_CARD, false }, /* terrestrial */
        { "udp",    ITEM_TYPE_STREAM, true },  /* udplite too */
        { "unsv",   ITEM_TYPE_STREAM, true },
        { "upnp",   ITEM_TYPE_FILE, true },
        { "usdigi", ITEM_TYPE_CARD, false }, /* usdigital */
        { "v4l",    ITEM_TYPE_CARD, false },
        { "vcd",    ITEM_TYPE_DISC, false },
        { "vdr",    ITEM_TYPE_STREAM, true },
        { "wasapi", ITEM_TYPE_CARD, false },
        { "window", ITEM_TYPE_CARD, false },
    };

#ifndef NDEBUG
    for( size_t i = 1; i < ARRAY_SIZE( tab ); i++ )
        assert( typecmp( (tab + i)->psz_scheme, tab + i - 1 ) > 0 );
#endif

    *p_net = false;

    if( strstr( p_item->psz_uri, "://" ) == NULL )
        return ITEM_TYPE_UNKNOWN; /* invalid URI */

    const struct item_type_entry *e =
        bsearch( p_item->psz_uri, tab, ARRAY_SIZE( tab ),
                 sizeof( tab[0] ), typecmp );
    if( e == NULL )
        return ITEM_TYPE_UNKNOWN;

    *p_net = e->b_net;
    return e->i_type;
}