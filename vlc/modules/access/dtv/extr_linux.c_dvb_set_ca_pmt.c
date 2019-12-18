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
typedef  int /*<<< orphan*/  en50221_capmt_info_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cam; } ;
typedef  TYPE_1__ dvb_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  en50221_SetCAPMT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool dvb_set_ca_pmt (dvb_device_t *d, en50221_capmt_info_t *p_capmtinfo)
{
    if (d->cam != NULL)
    {
        en50221_SetCAPMT (d->cam, p_capmtinfo);
        return true;
    }
    return false;
}