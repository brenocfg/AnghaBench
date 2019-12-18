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
typedef  scalar_t__ (* tuner_setup_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ dvb_set_inversion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dvb_tune (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int Tune (vlc_object_t *obj, dvb_device_t *dev, tuner_setup_t pf_setup,
                 uint64_t freq)
{
    if (pf_setup(obj, dev, freq)
     || dvb_set_inversion (dev, var_InheritInteger (obj, "dvb-inversion"))
     || dvb_tune (dev))
        return VLC_EGENERIC;
    return VLC_SUCCESS;
}