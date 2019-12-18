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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  time_interleaving; int /*<<< orphan*/  segment_count; int /*<<< orphan*/  code_rate; int /*<<< orphan*/  modulation; } ;
typedef  TYPE_1__ isdbt_layer_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTV_DELIVERY_SYSTEM ; 
 unsigned int DTV_ISDBT_LAYERA_FEC ; 
 scalar_t__ DTV_ISDBT_LAYERA_MODULATION ; 
 scalar_t__ DTV_ISDBT_LAYERA_SEGMENT_COUNT ; 
 scalar_t__ DTV_ISDBT_LAYERA_TIME_INTERLEAVING ; 
 unsigned int DTV_ISDBT_LAYERB_FEC ; 
 int /*<<< orphan*/  QAM_AUTO ; 
 int /*<<< orphan*/  SYS_ISDBT ; 
 int /*<<< orphan*/  dvb_parse_fec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_parse_modulation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dvb_set_props (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_set_isdbt_layer (dvb_device_t *d, unsigned num,
                                const isdbt_layer_t *l)
{
    uint32_t mod = dvb_parse_modulation (l->modulation, QAM_AUTO);
    uint32_t fec = dvb_parse_fec (l->code_rate);
    uint32_t count = l->segment_count;
    uint32_t ti = l->time_interleaving;

    num *= DTV_ISDBT_LAYERB_FEC - DTV_ISDBT_LAYERA_FEC;

    return dvb_set_props (d, 5, DTV_DELIVERY_SYSTEM, SYS_ISDBT,
                          DTV_ISDBT_LAYERA_FEC + num, fec,
                          DTV_ISDBT_LAYERA_MODULATION + num, mod,
                          DTV_ISDBT_LAYERA_SEGMENT_COUNT + num, count,
                          DTV_ISDBT_LAYERA_TIME_INTERLEAVING + num, ti);
}