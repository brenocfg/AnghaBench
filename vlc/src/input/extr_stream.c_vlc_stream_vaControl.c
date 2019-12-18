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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_6__ {int (* pf_control ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/ * block; int /*<<< orphan*/ * peek; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ stream_priv_t ;

/* Variables and functions */
#define  STREAM_SET_SEEKPOINT 129 
#define  STREAM_SET_TITLE 128 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int vlc_stream_vaControl(stream_t *s, int cmd, va_list args)
{
    stream_priv_t *priv = (stream_priv_t *)s;

    switch (cmd)
    {
        case STREAM_SET_TITLE:
        case STREAM_SET_SEEKPOINT:
        {
            int ret = s->pf_control(s, cmd, args);
            if (ret != VLC_SUCCESS)
                return ret;

            priv->offset = 0;

            if (priv->peek != NULL)
            {
                block_Release(priv->peek);
                priv->peek = NULL;
            }

            if (priv->block != NULL)
            {
                block_Release(priv->block);
                priv->block = NULL;
            }

            return VLC_SUCCESS;
        }
    }
    return s->pf_control(s, cmd, args);
}