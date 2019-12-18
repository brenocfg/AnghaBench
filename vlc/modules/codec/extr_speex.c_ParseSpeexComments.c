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
typedef  int /*<<< orphan*/  ogg_packet ;
struct TYPE_8__ {scalar_t__ p_description; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_9__ {TYPE_1__* p_header; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  modeName; } ;
struct TYPE_7__ {size_t mode; scalar_t__ vbr; } ;
typedef  TYPE_4__ SpeexMode ;

/* Variables and functions */
 size_t SPEEX_NB_MODES ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__** speex_mode_list ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vlc_meta_New () ; 

__attribute__((used)) static void ParseSpeexComments( decoder_t *p_dec, ogg_packet *p_oggpacket )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    const SpeexMode *p_mode;

    assert( p_sys->p_header->mode < SPEEX_NB_MODES );

    p_mode = speex_mode_list[p_sys->p_header->mode];
    assert( p_mode != NULL );

    if( !p_dec->p_description )
    {
        p_dec->p_description = vlc_meta_New();
        if( !p_dec->p_description )
            return;
    }

    /* */
    char *psz_mode;
    if( asprintf( &psz_mode, "%s%s", p_mode->modeName, p_sys->p_header->vbr ? " VBR" : "" ) >= 0 )
    {
        vlc_meta_AddExtra( p_dec->p_description, _("Mode"), psz_mode );
        free( psz_mode );
    }

    /* TODO: finish comments parsing */
    VLC_UNUSED( p_oggpacket );
}