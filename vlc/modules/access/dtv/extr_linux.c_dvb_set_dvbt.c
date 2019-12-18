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
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTV_BANDWIDTH_HZ ; 
 int /*<<< orphan*/  DTV_CLEAR ; 
 int /*<<< orphan*/  DTV_CODE_RATE_HP ; 
 int /*<<< orphan*/  DTV_CODE_RATE_LP ; 
 int /*<<< orphan*/  DTV_DELIVERY_DVB_T ; 
 int /*<<< orphan*/  DTV_DELIVERY_SYSTEM ; 
 int /*<<< orphan*/  DTV_FREQUENCY ; 
 int /*<<< orphan*/  DTV_GUARD_INTERVAL ; 
 int /*<<< orphan*/  DTV_HIERARCHY ; 
 int /*<<< orphan*/  DTV_MODULATION ; 
 int /*<<< orphan*/  DTV_TRANSMISSION_MODE ; 
 int /*<<< orphan*/  QAM_AUTO ; 
 int /*<<< orphan*/  SYS_DVBT ; 
 scalar_t__ dvb_find_frontend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_bandwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_fec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_guard (int /*<<< orphan*/ ) ; 
 int dvb_parse_hierarchy (int) ; 
 int /*<<< orphan*/  dvb_parse_modulation (char const*,int /*<<< orphan*/ ) ; 
 int dvb_parse_transmit_mode (int) ; 
 int dvb_set_props (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int dvb_set_dvbt (dvb_device_t *d, uint32_t freq, const char *modstr,
                  uint32_t fec_hp, uint32_t fec_lp, uint32_t bandwidth,
                  int transmit_mode, uint32_t guard, int hierarchy)
{
    uint32_t mod = dvb_parse_modulation (modstr, QAM_AUTO);
    fec_hp = dvb_parse_fec (fec_hp);
    fec_lp = dvb_parse_fec (fec_lp);
    bandwidth = dvb_parse_bandwidth (bandwidth);
    transmit_mode = dvb_parse_transmit_mode (transmit_mode);
    guard = dvb_parse_guard (guard);
    hierarchy = dvb_parse_hierarchy (hierarchy);

    if (dvb_find_frontend (d, DTV_DELIVERY_DVB_T))
        return -1;
    return dvb_set_props (d, 10, DTV_CLEAR, 0, DTV_DELIVERY_SYSTEM, SYS_DVBT,
                          DTV_FREQUENCY, freq, DTV_MODULATION, mod,
                          DTV_CODE_RATE_HP, fec_hp, DTV_CODE_RATE_LP, fec_lp,
                          DTV_BANDWIDTH_HZ, bandwidth,
                          DTV_TRANSMISSION_MODE, transmit_mode,
                          DTV_GUARD_INTERVAL, guard,
                          DTV_HIERARCHY, hierarchy);
}