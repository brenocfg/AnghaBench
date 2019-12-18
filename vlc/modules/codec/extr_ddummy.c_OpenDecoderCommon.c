#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  psz_file ;
typedef  int /*<<< orphan*/  p_dec ;
struct TYPE_5__ {int /*<<< orphan*/  fmt_in; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  pf_decode; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ decoder_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBlock ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,void*) ; 
 int var_InheritBool (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

__attribute__((used)) static int OpenDecoderCommon( vlc_object_t *p_this, bool b_force_dump )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    char psz_file[10 + 3 * sizeof (p_dec)];

    snprintf( psz_file, sizeof( psz_file), "stream.%p", (void *)p_dec );

    if( !b_force_dump )
        b_force_dump = var_InheritBool( p_dec, "dummy-save-es" );
    if( b_force_dump )
    {
        FILE *stream = vlc_fopen( psz_file, "wb" );
        if( stream == NULL )
        {
            msg_Err( p_dec, "cannot create `%s'", psz_file );
            return VLC_EGENERIC;
        }
        msg_Dbg( p_dec, "dumping stream to file `%s'", psz_file );
        p_dec->p_sys = (void *)stream;
    }
    else
        p_dec->p_sys = NULL;

    /* Set callbacks */
    p_dec->pf_decode = DecodeBlock;

    es_format_Copy( &p_dec->fmt_out, &p_dec->fmt_in );

    return VLC_SUCCESS;
}