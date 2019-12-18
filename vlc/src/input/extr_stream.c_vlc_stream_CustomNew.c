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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ vlc_iconv_t ;
struct TYPE_8__ {int /*<<< orphan*/ * p_input_item; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/ * pf_readdir; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/ * pf_read; int /*<<< orphan*/ * s; int /*<<< orphan*/ * psz_url; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_7__ {int char_width; int little_endian; scalar_t__ conv; } ;
struct TYPE_9__ {void (* destroy ) (TYPE_2__*) ;int eof; TYPE_1__ text; scalar_t__ offset; int /*<<< orphan*/ * peek; int /*<<< orphan*/ * block; TYPE_2__ stream; } ;
typedef  TYPE_3__ stream_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_3__* vlc_custom_create (int /*<<< orphan*/ *,int,char const*) ; 

stream_t *vlc_stream_CustomNew(vlc_object_t *parent,
                               void (*destroy)(stream_t *), size_t size,
                               const char *type_name)
{
    stream_priv_t *priv = vlc_custom_create(parent, sizeof (*priv) + size,
                                            type_name);
    if (unlikely(priv == NULL))
        return NULL;

    stream_t *s = &priv->stream;

    s->psz_url = NULL;
    s->s = NULL;
    s->pf_read = NULL;
    s->pf_block = NULL;
    s->pf_readdir = NULL;
    s->pf_seek = NULL;
    s->pf_control = NULL;
    s->p_sys = NULL;
    s->p_input_item = NULL;
    assert(destroy != NULL);
    priv->destroy = destroy;
    priv->block = NULL;
    priv->peek = NULL;
    priv->offset = 0;
    priv->eof = false;

    /* UTF16 and UTF32 text file conversion */
    priv->text.conv = (vlc_iconv_t)(-1);
    priv->text.char_width = 1;
    priv->text.little_endian = false;

    return s;
}