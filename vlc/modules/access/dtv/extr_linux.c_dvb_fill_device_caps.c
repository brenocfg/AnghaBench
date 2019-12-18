#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend_info {int caps; int /*<<< orphan*/  symbol_rate_max; int /*<<< orphan*/  symbol_rate_min; int /*<<< orphan*/  frequency_max; int /*<<< orphan*/  frequency_min; } ;
struct TYPE_9__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  frontend; } ;
typedef  TYPE_3__ dvb_device_t ;
struct TYPE_8__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_7__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_10__ {int b_can_cam_auto; TYPE_2__ symbolrate; TYPE_1__ frequency; } ;
typedef  TYPE_4__ dvb_device_caps_t ;

/* Variables and functions */
 int FE_CAN_QAM_AUTO ; 
 int /*<<< orphan*/  FE_GET_INFO ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_frontend_info*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int dvb_fill_device_caps(dvb_device_t *d, dvb_device_caps_t *caps)
{
    struct dvb_frontend_info info;
    if (ioctl (d->frontend, FE_GET_INFO, &info) < 0)
    {
        msg_Err (d->obj, "cannot get frontend info: %s",
                 vlc_strerror_c(errno));
        return -1;
    }

    caps->frequency.min = info.frequency_min;
    caps->frequency.max = info.frequency_max;
    caps->symbolrate.min = info.symbol_rate_min;
    caps->symbolrate.max = info.symbol_rate_max;
    caps->b_can_cam_auto = ( info.caps & FE_CAN_QAM_AUTO );

    return 0;
}