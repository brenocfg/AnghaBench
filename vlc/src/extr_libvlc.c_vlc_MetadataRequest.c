#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
typedef  int /*<<< orphan*/  input_preparser_callbacks_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_meta_request_option_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  input_preparser_Push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,int,void*) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int vlc_MetadataRequest(libvlc_int_t *libvlc, input_item_t *item,
                        input_item_meta_request_option_t i_options,
                        const input_preparser_callbacks_t *cbs,
                        void *cbs_userdata,
                        int timeout, void *id)
{
    libvlc_priv_t *priv = libvlc_priv(libvlc);

    if (unlikely(priv->parser == NULL))
        return VLC_ENOMEM;

    input_preparser_Push( priv->parser, item, i_options, cbs, cbs_userdata, timeout, id );
    return VLC_SUCCESS;

}