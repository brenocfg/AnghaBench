#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stream_extractor_private {int /*<<< orphan*/  object; scalar_t__ source; scalar_t__ module; int /*<<< orphan*/  (* pf_clean ) (struct stream_extractor_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_unneed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct stream_extractor_private*) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Delete (scalar_t__) ; 

__attribute__((used)) static void se_Release( struct stream_extractor_private* priv )
{
    if( priv->pf_clean )
        priv->pf_clean( priv );

    if( priv->module )
    {
        module_unneed( priv->object, priv->module );

        if( priv->source )
            vlc_stream_Delete( priv->source );
    }

    vlc_object_delete(priv->object);
}