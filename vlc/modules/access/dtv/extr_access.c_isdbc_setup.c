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
 int dvb_set_isdbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritCodeRate (int /*<<< orphan*/ *,char*) ; 
 unsigned int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritModulation (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int isdbc_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");
    uint32_t fec = var_InheritCodeRate (obj, "dvb-fec");
    unsigned srate = var_InheritInteger (obj, "dvb-srate");

    return dvb_set_isdbc (dev, freq, mod, srate, fec);
}