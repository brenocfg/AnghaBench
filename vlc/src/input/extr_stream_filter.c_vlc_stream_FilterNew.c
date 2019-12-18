#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vlc_stream_filter_private {int /*<<< orphan*/ * module; } ;
struct TYPE_9__ {int /*<<< orphan*/ * psz_filepath; struct TYPE_9__* s; int /*<<< orphan*/ * psz_url; int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  StreamDelete ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,char const*,int) ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_CommonDelete (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_parent (TYPE_1__*) ; 
 TYPE_1__* vlc_stream_CustomNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 struct vlc_stream_filter_private* vlc_stream_Private (TYPE_1__*) ; 

stream_t *vlc_stream_FilterNew( stream_t *p_source,
                                const char *psz_stream_filter )
{
    assert(p_source != NULL);

    struct vlc_stream_filter_private *priv;
    stream_t *s = vlc_stream_CustomNew(vlc_object_parent(p_source),
                                       StreamDelete, sizeof (*priv),
                                       "stream filter");
    if( s == NULL )
        return NULL;

    priv = vlc_stream_Private(s);
    s->p_input_item = p_source->p_input_item;

    if( p_source->psz_url != NULL )
    {
        s->psz_url = strdup( p_source->psz_url );
        if( unlikely(s->psz_url == NULL) )
            goto error;

        if( p_source->psz_filepath != NULL )
            s->psz_filepath = strdup( p_source->psz_filepath );
    }
    s->s = p_source;

    /* */
    priv->module = module_need(s, "stream_filter", psz_stream_filter, true);
    if (priv->module == NULL)
        goto error;

    return s;
error:
    free(s->psz_filepath);
    stream_CommonDelete( s );
    return NULL;
}