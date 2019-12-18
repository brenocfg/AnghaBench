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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  isdbt_layer_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTV_BANDWIDTH_HZ ; 
 int /*<<< orphan*/  DTV_CLEAR ; 
 int /*<<< orphan*/  DTV_DELIVERY_ISDB_T ; 
 int /*<<< orphan*/  DTV_DELIVERY_SYSTEM ; 
 int /*<<< orphan*/  DTV_FREQUENCY ; 
 int /*<<< orphan*/  DTV_GUARD_INTERVAL ; 
 int /*<<< orphan*/  DTV_ISDBT_LAYER_ENABLED ; 
 int /*<<< orphan*/  SYS_ISDBT ; 
 scalar_t__ dvb_find_frontend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_bandwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_guard (int /*<<< orphan*/ ) ; 
 int dvb_parse_transmit_mode (int) ; 
 scalar_t__ dvb_set_isdbt_layer (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/  const*) ; 
 scalar_t__ dvb_set_props (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dvb_set_isdbt (dvb_device_t *d, uint32_t freq, uint32_t bandwidth,
                   int transmit_mode, uint32_t guard,
                   const isdbt_layer_t layers[3])
{
    bandwidth = dvb_parse_bandwidth (bandwidth);
    transmit_mode = dvb_parse_transmit_mode (transmit_mode);
    guard = dvb_parse_guard (guard);

    if (dvb_find_frontend (d, DTV_DELIVERY_ISDB_T))
        return -1;
    if (dvb_set_props (d, 6, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_ISDBT,
                       DTV_FREQUENCY, freq, DTV_BANDWIDTH_HZ, bandwidth,
                       DTV_GUARD_INTERVAL, guard,
                       DTV_ISDBT_LAYER_ENABLED, 0x7 /* all layers enabled */))
        return -1;
    for (unsigned i = 0; i < 3; i++)
        if (dvb_set_isdbt_layer (d, i, layers + i))
            return -1;
    return 0;
}