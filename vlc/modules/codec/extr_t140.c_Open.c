#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/ * psz_encoding; } ;
struct TYPE_7__ {int i_codec; int /*<<< orphan*/  i_cat; TYPE_1__ subs; } ;
struct TYPE_6__ {int /*<<< orphan*/  force; } ;
struct TYPE_8__ {TYPE_3__ fmt_out; int /*<<< orphan*/  pf_encode_sub; int /*<<< orphan*/ * p_sys; TYPE_2__ obj; } ;
typedef  TYPE_4__ encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  Encode ; 
 int /*<<< orphan*/  SPU_ES ; 
#define  VLC_CODEC_ITU_T140 129 
#define  VLC_CODEC_SUBT 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    encoder_t *p_enc = (encoder_t *)p_this;

    switch( p_enc->fmt_out.i_codec )
    {
        case VLC_CODEC_SUBT:
            if( ( p_enc->fmt_out.subs.psz_encoding != NULL )
             && strcasecmp( p_enc->fmt_out.subs.psz_encoding, "utf8" )
             && strcasecmp( p_enc->fmt_out.subs.psz_encoding, "UTF-8" ) )
            {
                msg_Err( p_this, "Only UTF-8 encoding supported" );
                return VLC_EGENERIC;
            }
        case VLC_CODEC_ITU_T140:
            break;

        default:
            if( !p_enc->obj.force )
                return VLC_EGENERIC;

            p_enc->fmt_out.i_codec = VLC_CODEC_ITU_T140;
    }

    p_enc->p_sys = NULL;

    p_enc->pf_encode_sub = Encode;
    p_enc->fmt_out.i_cat = SPU_ES;
    return VLC_SUCCESS;
}