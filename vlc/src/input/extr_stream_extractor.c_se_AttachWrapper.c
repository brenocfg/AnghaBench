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
struct stream_extractor_private {TYPE_1__* wrapper; TYPE_1__* source; scalar_t__ (* pf_init ) (struct stream_extractor_private*,TYPE_1__*) ;} ;
struct TYPE_9__ {struct stream_extractor_private* p_sys; int /*<<< orphan*/  p_input_item; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  se_StreamDelete ; 
 int /*<<< orphan*/  stream_CommonDelete (TYPE_1__*) ; 
 TYPE_1__* stream_FilterChainNew (TYPE_1__*,char*) ; 
 scalar_t__ stub1 (struct stream_extractor_private*,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_object_parent (TYPE_1__*) ; 
 TYPE_1__* vlc_stream_CommonNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
se_AttachWrapper( struct stream_extractor_private* priv, stream_t* source )
{
    stream_t* s = vlc_stream_CommonNew( vlc_object_parent(source),
                                        se_StreamDelete );

    if( unlikely( !s ) )
        return VLC_ENOMEM;

    if( priv->pf_init( priv, s ) )
    {
        stream_CommonDelete( s );
        return VLC_EGENERIC;
    }

    priv->wrapper = s;
    priv->wrapper->p_input_item = source->p_input_item;
    priv->wrapper->p_sys = priv;

    priv->source = source;

    priv->wrapper = stream_FilterChainNew( priv->wrapper, "cache" );
    return VLC_SUCCESS;
}