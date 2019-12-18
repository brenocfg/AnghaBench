#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct enc_picture_free_t {TYPE_5__* p_enc; TYPE_4__* p_pic; } ;
struct TYPE_17__ {TYPE_2__* p; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_18__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ encoder_t ;
struct TYPE_19__ {TYPE_1__* p_format; } ;
typedef  TYPE_6__ encoder_sys_t ;
struct TYPE_20__ {int /*<<< orphan*/  format; TYPE_3__* components; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_16__ {int stride; int length; int /*<<< orphan*/  h_shift; int /*<<< orphan*/  v_shift; int /*<<< orphan*/  data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {int i_pitch; int i_lines; int /*<<< orphan*/  p_pixels; int /*<<< orphan*/  i_visible_lines; int /*<<< orphan*/  i_visible_pitch; } ;
struct TYPE_14__ {scalar_t__ chroma_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_7__ SchroFrame ;

/* Variables and functions */
 int /*<<< orphan*/  EncSchroFrameFree ; 
 scalar_t__ SCHRO_CHROMA_422 ; 
 scalar_t__ SCHRO_CHROMA_444 ; 
 int /*<<< orphan*/  SCHRO_FRAME_FORMAT_H_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCHRO_FRAME_FORMAT_U8_420 ; 
 int /*<<< orphan*/  SCHRO_FRAME_FORMAT_U8_422 ; 
 int /*<<< orphan*/  SCHRO_FRAME_FORMAT_U8_444 ; 
 int /*<<< orphan*/  SCHRO_FRAME_FORMAT_V_SHIFT (int /*<<< orphan*/ ) ; 
 struct enc_picture_free_t* malloc (int) ; 
 TYPE_7__* schro_frame_new () ; 
 int /*<<< orphan*/  schro_frame_set_free_callback (TYPE_7__*,int /*<<< orphan*/ ,struct enc_picture_free_t*) ; 
 int /*<<< orphan*/  schro_frame_unref (TYPE_7__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SchroFrame *CreateSchroFrameFromInputPic( encoder_t *p_enc,  picture_t *p_pic )
{
    encoder_sys_t *p_sys = p_enc->p_sys;
    SchroFrame *p_schroframe = schro_frame_new();
    struct enc_picture_free_t *p_free;

    if( !p_schroframe )
        return NULL;

    if( !p_pic )
        return NULL;

    p_schroframe->format = SCHRO_FRAME_FORMAT_U8_420;
    if( p_sys->p_format->chroma_format == SCHRO_CHROMA_422 )
    {
        p_schroframe->format = SCHRO_FRAME_FORMAT_U8_422;
    }
    else if( p_sys->p_format->chroma_format == SCHRO_CHROMA_444 )
    {
        p_schroframe->format = SCHRO_FRAME_FORMAT_U8_444;
    }

    p_schroframe->width  = p_sys->p_format->width;
    p_schroframe->height = p_sys->p_format->height;

    p_free = malloc( sizeof( *p_free ) );
    if( unlikely( p_free == NULL ) ) {
        schro_frame_unref( p_schroframe );
        return NULL;
    }

    p_free->p_pic = p_pic;
    p_free->p_enc = p_enc;
    schro_frame_set_free_callback( p_schroframe, EncSchroFrameFree, p_free );

    for( int i=0; i<3; i++ )
    {
        p_schroframe->components[i].width  = p_pic->p[i].i_visible_pitch;
        p_schroframe->components[i].stride = p_pic->p[i].i_pitch;
        p_schroframe->components[i].height = p_pic->p[i].i_visible_lines;
        p_schroframe->components[i].length =
            p_pic->p[i].i_pitch * p_pic->p[i].i_lines;
        p_schroframe->components[i].data   = p_pic->p[i].p_pixels;

        if( i!=0 )
        {
            p_schroframe->components[i].v_shift =
                SCHRO_FRAME_FORMAT_V_SHIFT( p_schroframe->format );
            p_schroframe->components[i].h_shift =
                SCHRO_FRAME_FORMAT_H_SHIFT( p_schroframe->format );
        }
    }

    return p_schroframe;
}