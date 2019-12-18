#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_access_stream_private {int /*<<< orphan*/ * input; } ;
struct TYPE_11__ {struct TYPE_11__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/ * pf_read; int /*<<< orphan*/ * pf_block; int /*<<< orphan*/ * psz_url; int /*<<< orphan*/ * p_input_item; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  AStreamControl ; 
 int /*<<< orphan*/  AStreamDestroy ; 
 int /*<<< orphan*/ * AStreamReadBlock ; 
 int /*<<< orphan*/ * AStreamReadStream ; 
 int /*<<< orphan*/  AStreamSeek ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 TYPE_1__* access_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * input_GetItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 
 TYPE_1__* stream_FilterChainNew (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 TYPE_1__* vlc_stream_CustomNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_stream_Delete (TYPE_1__*) ; 
 struct vlc_access_stream_private* vlc_stream_Private (TYPE_1__*) ; 

stream_t *stream_AccessNew(vlc_object_t *parent, input_thread_t *input,
                           es_out_t *out, bool preparsing, const char *url)
{
    stream_t *access = access_New(parent, input, out, preparsing, url);
    if (access == NULL)
        return NULL;

    stream_t *s;

    if (access->pf_block != NULL || access->pf_read != NULL)
    {
        struct vlc_access_stream_private *priv;
        s = vlc_stream_CustomNew(VLC_OBJECT(access), AStreamDestroy,
                                 sizeof(*priv), "stream");

        if (unlikely(s == NULL))
        {
            vlc_stream_Delete(access);
            return NULL;
        }
        priv = vlc_stream_Private(s);
        priv->input = input;

        s->p_input_item = input ? input_GetItem(input) : NULL;
        s->psz_url = strdup(access->psz_url);
        if (unlikely(s->psz_url == NULL))
        {
            vlc_object_delete(s);
            vlc_stream_Delete(access);
            return NULL;
        }

        if (access->pf_block != NULL)
            s->pf_block = AStreamReadBlock;
        if (access->pf_read != NULL)
            s->pf_read = AStreamReadStream;

        s->pf_seek = AStreamSeek;
        s->pf_control = AStreamControl;
        s->p_sys = access;

        s = stream_FilterChainNew(s, "prefetch,cache");
    }
    else
        s = access;

    return s;
}