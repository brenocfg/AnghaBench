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
 int /*<<< orphan*/  dvb_set_sec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char,unsigned int,unsigned int,unsigned int) ; 
 unsigned int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char var_InheritPolarization (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sec_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    char pol = var_InheritPolarization (obj);
    unsigned lowf = var_InheritInteger (obj, "dvb-lnb-low");
    unsigned highf = var_InheritInteger (obj, "dvb-lnb-high");
    unsigned switchf = var_InheritInteger (obj, "dvb-lnb-switch");

    dvb_set_sec (dev, freq, pol, lowf, highf, switchf);
}