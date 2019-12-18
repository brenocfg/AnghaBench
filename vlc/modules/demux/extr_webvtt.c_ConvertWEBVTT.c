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
struct TYPE_3__ {char* psz_text; char* psz_id; char* psz_attrs; } ;
typedef  TYPE_1__ webvtt_cue_t ;
typedef  char uint8_t ;
struct vlc_memstream {int /*<<< orphan*/  length; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (char*,size_t const) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/ * block_heap_Alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_write (struct vlc_memstream*,char*,size_t const) ; 

__attribute__((used)) static block_t *ConvertWEBVTT( const webvtt_cue_t *p_cue, bool b_continued )
{
    struct vlc_memstream stream;

    if( vlc_memstream_open( &stream ) )
        return NULL;

    const size_t paylsize = 8 + strlen( p_cue->psz_text );
    const size_t idensize = (p_cue->psz_id) ? 8 + strlen( p_cue->psz_id ) : 0;
    const size_t attrsize = (p_cue->psz_attrs) ? 8 + strlen( p_cue->psz_attrs ) : 0;
    const size_t vttcsize = 8 + paylsize + attrsize + idensize;

    uint8_t vttcbox[8] = { 0, 0, 0, 0, 'v', 't', 't', 'c' };
    if( b_continued )
        vttcbox[7] = 'x';
    SetDWBE( vttcbox, vttcsize );
    vlc_memstream_write( &stream, vttcbox, 8 );

    if( p_cue->psz_id )
    {
        uint8_t idenbox[8] = { 0, 0, 0, 0, 'i', 'd', 'e', 'n' };
        SetDWBE( idenbox, idensize );
        vlc_memstream_write( &stream, idenbox, 8 );
        vlc_memstream_write( &stream, p_cue->psz_id, idensize - 8 );
    }

    if( p_cue->psz_attrs )
    {
        uint8_t attrbox[8] = { 0, 0, 0, 0, 's', 't', 't', 'g' };
        SetDWBE( attrbox, attrsize );
        vlc_memstream_write( &stream, attrbox, 8 );
        vlc_memstream_write( &stream, p_cue->psz_attrs, attrsize - 8 );
    }

    uint8_t paylbox[8] = { 0, 0, 0, 0, 'p', 'a', 'y', 'l' };
    SetDWBE( paylbox, paylsize );
    vlc_memstream_write( &stream, paylbox, 8 );
    vlc_memstream_write( &stream, p_cue->psz_text, paylsize - 8 );

    if( vlc_memstream_close( &stream ) == VLC_SUCCESS )
        return block_heap_Alloc( stream.ptr, stream.length );
    else
        return NULL;
}