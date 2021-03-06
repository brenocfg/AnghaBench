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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/ * opaque; } ;
typedef  TYPE_1__ vlc_decoder_device ;
typedef  int /*<<< orphan*/  decoder_device_nvdec_t ;

/* Variables and functions */
 scalar_t__ VLC_DECODER_DEVICE_NVDEC ; 

__attribute__((used)) static inline decoder_device_nvdec_t *GetNVDECOpaqueDevice(vlc_decoder_device *device)
{
    if (device == NULL || device->type != VLC_DECODER_DEVICE_NVDEC)
        return NULL;
    return device->opaque;
}