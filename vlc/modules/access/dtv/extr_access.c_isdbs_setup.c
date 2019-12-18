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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int dvb_set_isdbs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int isdbs_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    uint16_t ts_id = var_InheritInteger (obj, "dvb-ts-id");

    int ret = dvb_set_isdbs (dev, freq, ts_id);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}