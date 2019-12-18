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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int dvb_set_dvbs2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,void*,void*,int,int,void*) ; 
 int /*<<< orphan*/  sec_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* var_InheritCodeRate (int /*<<< orphan*/ *,char*) ; 
 void* var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritModulation (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int dvbs2_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    uint32_t srate = var_InheritInteger (obj, "dvb-srate");
    int pilot = var_InheritInteger (obj, "dvb-pilot");
    int rolloff = var_InheritInteger (obj, "dvb-rolloff");
    uint8_t sid = var_InheritInteger (obj, "dvb-stream");

    int ret = dvb_set_dvbs2 (dev, freq, mod, srate, fec, pilot, rolloff, sid);
    if (ret == 0)
        sec_setup (obj, dev, freq);
    return ret;
}