#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_fast32_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {size_t i_extra; char* p_extra; } ;
struct TYPE_10__ {TYPE_2__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_11__ {TYPE_3__* p_context; TYPE_1__* p_codec; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_9__ {size_t extradata_size; int /*<<< orphan*/ * extradata; } ;
struct TYPE_7__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_SVQ3 ; 
 size_t FF_INPUT_BUFFER_PADDING_SIZE ; 
 int GetDWBE (int /*<<< orphan*/ *) ; 
 void* av_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void ffmpeg_InitCodec( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    size_t i_size = p_dec->fmt_in.i_extra;

    if( !i_size ) return;

    if( p_sys->p_codec->id == AV_CODEC_ID_SVQ3 )
    {
        uint8_t *p;

        p_sys->p_context->extradata_size = i_size + 12;
        p = p_sys->p_context->extradata =
            av_malloc( p_sys->p_context->extradata_size +
                       FF_INPUT_BUFFER_PADDING_SIZE );
        if( !p )
            return;

        memcpy( &p[0],  "SVQ3", 4 );
        memset( &p[4], 0, 8 );
        memcpy( &p[12], p_dec->fmt_in.p_extra, i_size );

        /* Now remove all atoms before the SMI one */
        if( p_sys->p_context->extradata_size > 0x5a &&
            strncmp( (char*)&p[0x56], "SMI ", 4 ) )
        {
            uint8_t *psz = &p[0x52];

            while( psz < &p[p_sys->p_context->extradata_size - 8] )
            {
                uint_fast32_t atom_size = GetDWBE( psz );
                if( atom_size <= 1 )
                {
                    /* FIXME handle 1 as long size */
                    break;
                }
                if( !strncmp( (char*)&psz[4], "SMI ", 4 ) )
                {
                    memmove( &p[0x52], psz,
                             &p[p_sys->p_context->extradata_size] - psz );
                    break;
                }

                psz += atom_size;
            }
        }
    }
    else
    {
        p_sys->p_context->extradata_size = i_size;
        p_sys->p_context->extradata =
            av_malloc( i_size + FF_INPUT_BUFFER_PADDING_SIZE );
        if( p_sys->p_context->extradata )
        {
            memcpy( p_sys->p_context->extradata,
                    p_dec->fmt_in.p_extra, i_size );
            memset( p_sys->p_context->extradata + i_size,
                    0, FF_INPUT_BUFFER_PADDING_SIZE );
        }
    }
}