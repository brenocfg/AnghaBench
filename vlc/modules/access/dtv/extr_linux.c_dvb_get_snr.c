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
typedef  int uint16_t ;
struct TYPE_3__ {int frontend; } ;
typedef  TYPE_1__ dvb_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_READ_SNR ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 

float dvb_get_snr (dvb_device_t *d)
{
    uint16_t snr;

    if (d->frontend == -1 || ioctl (d->frontend, FE_READ_SNR, &snr) < 0)
        return 0.;
    return snr / 65535.;
}