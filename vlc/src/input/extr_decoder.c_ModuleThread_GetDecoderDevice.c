#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_decoder_device ;
struct TYPE_14__ {scalar_t__ MaxCLL; scalar_t__ MaxFALL; } ;
struct TYPE_15__ {TYPE_4__ lighting; int /*<<< orphan*/  mastering; } ;
struct TYPE_16__ {TYPE_5__ video; } ;
struct decoder_owner {int /*<<< orphan*/  lock; TYPE_6__ fmt; } ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;
struct TYPE_11__ {scalar_t__ MaxCLL; scalar_t__ MaxFALL; } ;
struct TYPE_12__ {TYPE_1__ lighting; int /*<<< orphan*/  mastering; } ;
struct TYPE_13__ {TYPE_2__ video; } ;
struct TYPE_17__ {TYPE_3__ fmt_out; } ;
typedef  TYPE_7__ decoder_t ;

/* Variables and functions */
 int CreateVoutIfNeeded (struct decoder_owner*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DecoderUpdateFormatLocked (struct decoder_owner*) ; 
 struct decoder_owner* dec_get_owner (TYPE_7__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_decoder_device * ModuleThread_GetDecoderDevice( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    enum vlc_vout_order vout_order;
    vlc_decoder_device *dec_device = NULL;
    int created_vout = CreateVoutIfNeeded(p_owner, NULL, &vout_order, &dec_device);
    if (created_vout == -1)
    {
        if ( dec_device )
            vlc_decoder_device_Release( dec_device );
        return NULL;  // error
    }
    if (created_vout == 1)
    {
        return dec_device; // new vout was created with a decoder device
    }

    bool need_format_update = false;
    if ( memcmp( &p_dec->fmt_out.video.mastering,
                 &p_owner->fmt.video.mastering,
                 sizeof(p_owner->fmt.video.mastering)) )
    {
        msg_Dbg(p_dec, "vout update: mastering data");
        need_format_update = true;
    }
    if ( p_dec->fmt_out.video.lighting.MaxCLL !=
         p_owner->fmt.video.lighting.MaxCLL ||
         p_dec->fmt_out.video.lighting.MaxFALL !=
         p_owner->fmt.video.lighting.MaxFALL )
    {
        msg_Dbg(p_dec, "vout update: lighting data");
        need_format_update = true;
    }

    if ( need_format_update )
    {
        /* the format has changed but we don't need a new vout */
        vlc_mutex_lock( &p_owner->lock );
        DecoderUpdateFormatLocked( p_owner );
        vlc_mutex_unlock( &p_owner->lock );
    }
    return dec_device;
}