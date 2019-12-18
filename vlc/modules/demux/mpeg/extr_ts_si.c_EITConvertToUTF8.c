#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_7__ {scalar_t__ p_instance; } ;
struct TYPE_9__ {scalar_t__ standard; TYPE_1__ arib; } ;
typedef  TYPE_3__ demux_sys_t ;
typedef  int /*<<< orphan*/  arib_decoder_t ;

/* Variables and functions */
 char* FromCharset (char*,unsigned char const*,size_t) ; 
 scalar_t__ TS_STANDARD_ARIB ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_3__*) ; 
 size_t arib_decode_buffer (int /*<<< orphan*/ *,unsigned char const*,size_t,char*,size_t) ; 
 int /*<<< orphan*/  arib_finalize_decoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * arib_get_decoder (scalar_t__) ; 
 int /*<<< orphan*/  arib_initialize_decoder (int /*<<< orphan*/ *) ; 
 scalar_t__ arib_instance_new (TYPE_2__*) ; 
 scalar_t__ calloc (size_t,int) ; 
 char* vlc_from_EIT (unsigned char const*,size_t) ; 

__attribute__((used)) static char *EITConvertToUTF8( demux_t *p_demux,
                               const unsigned char *psz_instring,
                               size_t i_length,
                               bool b_broken )
{
    demux_sys_t *p_sys = p_demux->p_sys;
#ifdef HAVE_ARIBB24
    if( p_sys->standard == TS_STANDARD_ARIB )
    {
        if ( !p_sys->arib.p_instance )
            p_sys->arib.p_instance = arib_instance_new( p_demux );
        if ( !p_sys->arib.p_instance )
            return NULL;
        arib_decoder_t *p_decoder = arib_get_decoder( p_sys->arib.p_instance );
        if ( !p_decoder )
            return NULL;

        char *psz_outstring = NULL;
        size_t i_out;

        i_out = i_length * 4;
        psz_outstring = (char*) calloc( i_out + 1, sizeof(char) );
        if( !psz_outstring )
            return NULL;

        arib_initialize_decoder( p_decoder );
        i_out = arib_decode_buffer( p_decoder, psz_instring, i_length,
                                    psz_outstring, i_out );
        arib_finalize_decoder( p_decoder );

        return psz_outstring;
    }
#else
    VLC_UNUSED(p_sys);
#endif
    /* Deal with no longer broken providers (no switch byte
      but sending ISO_8859-1 instead of ISO_6937) without
      removing them from the broken providers table
      (keep the entry for correctly handling recorded TS).
    */
    b_broken = b_broken && i_length && *psz_instring > 0x20;

    if( b_broken )
        return FromCharset( "ISO_8859-1", psz_instring, i_length );
    return vlc_from_EIT( psz_instring, i_length );
}