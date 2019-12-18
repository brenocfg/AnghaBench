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
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int (* pf_seek ) (TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int eof; scalar_t__ offset; TYPE_3__* block; TYPE_3__* peek; } ;
typedef  TYPE_2__ stream_priv_t ;
struct TYPE_9__ {scalar_t__ i_buffer; size_t p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int stub1 (TYPE_1__*,scalar_t__) ; 

int vlc_stream_Seek(stream_t *s, uint64_t offset)
{
    stream_priv_t *priv = (stream_priv_t *)s;

    priv->eof = false;

    block_t *peek = priv->peek;
    if (peek != NULL)
    {
        if (offset >= priv->offset
         && offset <= (priv->offset + peek->i_buffer))
        {   /* Seeking within the peek buffer */
            size_t fwd = offset - priv->offset;

            peek->p_buffer += fwd;
            peek->i_buffer -= fwd;
            priv->offset = offset;

            if (peek->i_buffer == 0)
            {
                priv->peek = NULL;
                block_Release(peek);
            }

            return VLC_SUCCESS;
        }
    }
    else
    {
        if (priv->offset == offset)
            return VLC_SUCCESS; /* Nothing to do! */
    }

    if (s->pf_seek == NULL)
        return VLC_EGENERIC;

    int ret = s->pf_seek(s, offset);
    if (ret != VLC_SUCCESS)
        return ret;

    priv->offset = offset;

    if (peek != NULL)
    {
        priv->peek = NULL;
        block_Release(peek);
    }

    if (priv->block != NULL)
    {
        block_Release(priv->block);
        priv->block = NULL;
    }

    return VLC_SUCCESS;
}