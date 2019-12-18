#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_2__* peek; TYPE_2__* block; } ;
typedef  TYPE_1__ stream_priv_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 scalar_t__ VLC_ENOMEM ; 
 TYPE_2__* block_Alloc (size_t) ; 
 TYPE_2__* block_TryRealloc (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_stream_ReadRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

ssize_t vlc_stream_Peek(stream_t *s, const uint8_t **restrict bufp, size_t len)
{
    stream_priv_t *priv = (stream_priv_t *)s;
    block_t *peek;

    peek = priv->peek;
    if (peek == NULL)
    {
        peek = priv->block;
        priv->peek = peek;
        priv->block = NULL;
    }

    if (peek == NULL)
    {
        peek = block_Alloc(len);
        if (unlikely(peek == NULL))
            return VLC_ENOMEM;

        peek->i_buffer = 0;
    }
    else
    if (peek->i_buffer < len)
    {
        size_t avail = peek->i_buffer;

        peek = block_TryRealloc(peek, 0, len);
        if (unlikely(peek == NULL))
            return VLC_ENOMEM;

        peek->i_buffer = avail;
    }

    priv->peek = peek;
    *bufp = peek->p_buffer;

    while (peek->i_buffer < len)
    {
        size_t avail = peek->i_buffer;
        ssize_t ret;

        ret = vlc_stream_ReadRaw(s, peek->p_buffer + avail, len - avail);
        if (ret < 0)
            continue;

        peek->i_buffer += ret;

        if (ret == 0)
            return peek->i_buffer;
    }

    return len;
}