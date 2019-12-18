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
struct TYPE_3__ {int /*<<< orphan*/  vout; int /*<<< orphan*/ * fmt; } ;
typedef  TYPE_1__ vout_device_configuration_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  VoutCheckFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VoutFixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int vout_EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

vlc_decoder_device *vout_GetDevice(const vout_device_configuration_t *cfg)
{
    vlc_decoder_device *dec_device = NULL;

    assert(cfg->fmt != NULL);

    if (!VoutCheckFormat(cfg->fmt))
        return NULL;

    video_format_t original;
    VoutFixFormat(&original, cfg->fmt);

    int res = vout_EnableWindow(cfg->vout, &original, &dec_device);
    video_format_Clean(&original);
    if (res != 0)
        return NULL;
    return dec_device;
}