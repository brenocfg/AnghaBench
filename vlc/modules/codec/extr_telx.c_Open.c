#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_12__ {int i_magazine; scalar_t__ i_page; } ;
struct TYPE_13__ {TYPE_2__ teletext; } ;
struct TYPE_14__ {scalar_t__ i_codec; TYPE_3__ subs; } ;
struct TYPE_11__ {scalar_t__ i_codec; } ;
struct TYPE_15__ {TYPE_4__ fmt_in; TYPE_1__ fmt_out; TYPE_6__* p_sys; int /*<<< orphan*/  pf_decode; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_16__ {int i_wanted_magazine; int i_wanted_page; void* b_ignore_sub_flag; int /*<<< orphan*/ * pi_active_national_set; scalar_t__ i_align; } ;
typedef  TYPE_6__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 scalar_t__ VLC_CODEC_TELETEXT ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,int,int,void*) ; 
 int /*<<< orphan*/ * ppi_national_subsets ; 
 void* var_CreateGetBool (TYPE_5__*,char*) ; 
 int var_CreateGetInteger (TYPE_5__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t *) p_this;
    decoder_sys_t *p_sys = NULL;
    int            i_val;


    if( p_dec->fmt_in.i_codec != VLC_CODEC_TELETEXT)
    {
        return VLC_EGENERIC;
    }

    p_dec->pf_decode = Decode;
    p_sys = p_dec->p_sys = calloc( 1, sizeof(*p_sys) );
    if( p_sys == NULL )
        return VLC_ENOMEM;
    p_dec->fmt_out.i_codec = 0;

    p_sys->i_align = 0;
    for ( int i = 0; i < 9; i++ )
        p_sys->pi_active_national_set[i] = ppi_national_subsets[1];

    i_val = var_CreateGetInteger( p_dec, "telx-override-page" );
    if( i_val == -1 && p_dec->fmt_in.subs.teletext.i_magazine < 9 &&
        ( p_dec->fmt_in.subs.teletext.i_magazine != 1 ||
          p_dec->fmt_in.subs.teletext.i_page != 0 ) ) /* ignore if TS demux wants page 100 (unlikely to be sub) */
    {
        bool b_val;
        p_sys->i_wanted_magazine = p_dec->fmt_in.subs.teletext.i_magazine;
        p_sys->i_wanted_page = p_dec->fmt_in.subs.teletext.i_page;

        b_val = var_CreateGetBool( p_dec, "telx-french-workaround" );
        if( p_sys->i_wanted_page < 100 &&
            (b_val || (p_sys->i_wanted_page % 16) >= 10))
        {
            /* See http://www.nada.kth.se/~ragge/vdr/ttxtsubs/TROUBLESHOOTING.txt
             * paragraph about French channels - they mix up decimal and
             * hexadecimal */
            p_sys->i_wanted_page = (p_sys->i_wanted_page / 10) * 16 +
                                   (p_sys->i_wanted_page % 10);
        }
    }
    else if( i_val <= 0 )
    {
        p_sys->i_wanted_magazine = -1;
        p_sys->i_wanted_page = -1;
    }
    else
    {
        p_sys->i_wanted_magazine = i_val / 100;
        p_sys->i_wanted_page = (((i_val % 100) / 10) << 4)
                               |((i_val % 100) % 10);
    }
    p_sys->b_ignore_sub_flag = var_CreateGetBool( p_dec,
                                    "telx-ignore-subtitle-flag" );

    msg_Dbg( p_dec, "starting telx on magazine %d page %02x flag %d",
             p_sys->i_wanted_magazine, p_sys->i_wanted_page,
             p_sys->b_ignore_sub_flag );

    return VLC_SUCCESS;

/*  error: */
/*     if (p_sys) { */
/*       free(p_sys); */
/*       p_sys = NULL; */
/*     } */
/*     return VLC_EGENERIC; */
}