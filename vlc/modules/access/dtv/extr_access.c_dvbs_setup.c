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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int dvb_set_dvbs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritCodeRate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int dvbs_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    uint32_t srate = var_InheritInteger (obj, "dvb-srate");

    int ret = dvb_set_dvbs (dev, freq, srate, fec);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}