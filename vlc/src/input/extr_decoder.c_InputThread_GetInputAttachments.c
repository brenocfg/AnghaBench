#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct decoder_owner {int /*<<< orphan*/  cbs_userdata; TYPE_1__* cbs; } ;
typedef  int /*<<< orphan*/  input_attachment_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_2__ {int (* get_attachments ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOOBJ ; 
 int VLC_SUCCESS ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int InputThread_GetInputAttachments( decoder_t *p_dec,
                                       input_attachment_t ***ppp_attachment,
                                       int *pi_attachment )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    if (!p_owner->cbs || !p_owner->cbs->get_attachments)
        return VLC_ENOOBJ;

    int ret = p_owner->cbs->get_attachments(p_dec, ppp_attachment,
                                            p_owner->cbs_userdata);
    if (ret < 0)
        return VLC_EGENERIC;
    *pi_attachment = ret;
    return VLC_SUCCESS;
}