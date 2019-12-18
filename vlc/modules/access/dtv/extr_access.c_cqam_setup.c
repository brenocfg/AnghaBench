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
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int dvb_set_cqam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* var_InheritModulation (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int cqam_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    const char *mod = var_InheritModulation (obj, "dvb-modulation");

    return dvb_set_cqam (dev, freq, mod);
}