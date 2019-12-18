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
struct TYPE_6__ {int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
typedef  int /*<<< orphan*/  input_preparser_callbacks_t ;
struct TYPE_7__ {int i_preparse_depth; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ input_item_t ;
typedef  int input_item_meta_request_option_t ;

/* Variables and functions */
 int META_REQUEST_OPTION_SCOPE_ANY ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_MetadataRequest (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/  const*,void*,int,void*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int libvlc_MetadataRequest(libvlc_int_t *libvlc, input_item_t *item,
                           input_item_meta_request_option_t i_options,
                           const input_preparser_callbacks_t *cbs,
                           void *cbs_userdata,
                           int timeout, void *id)
{
    libvlc_priv_t *priv = libvlc_priv(libvlc);
    assert(i_options & META_REQUEST_OPTION_SCOPE_ANY);

    if (unlikely(priv->parser == NULL))
        return VLC_ENOMEM;

    vlc_mutex_lock( &item->lock );
    if( item->i_preparse_depth == 0 )
        item->i_preparse_depth = 1;
    vlc_mutex_unlock( &item->lock );

    return vlc_MetadataRequest(libvlc, item, i_options, cbs, cbs_userdata, timeout, id);
}