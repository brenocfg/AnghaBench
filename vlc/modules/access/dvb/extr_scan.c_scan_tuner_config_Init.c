#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; int /*<<< orphan*/  delivery; void* inner_fec; void* coderate_hp; void* coderate_lp; } ;
typedef  TYPE_1__ scan_tuner_config_t ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_2__ scan_parameter_t ;

/* Variables and functions */
 void* SCAN_CODERATE_AUTO ; 
 int /*<<< orphan*/  SCAN_DELIVERY_DVB_C ; 
 int /*<<< orphan*/  SCAN_DELIVERY_DVB_S ; 
 int /*<<< orphan*/  SCAN_DELIVERY_DVB_T ; 
 int /*<<< orphan*/  SCAN_DELIVERY_UNKNOWN ; 
#define  SCAN_DVB_C 130 
#define  SCAN_DVB_S 129 
#define  SCAN_DVB_T 128 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void scan_tuner_config_Init( scan_tuner_config_t *p_cfg, const scan_parameter_t *p_params )
{
    memset( p_cfg, 0, sizeof(*p_cfg) );
    p_cfg->coderate_lp = SCAN_CODERATE_AUTO;
    p_cfg->coderate_hp = SCAN_CODERATE_AUTO;
    p_cfg->inner_fec = SCAN_CODERATE_AUTO;
    switch(p_params->type)
    {
        case SCAN_DVB_T: p_cfg->delivery = SCAN_DELIVERY_DVB_T; break;
        case SCAN_DVB_S: p_cfg->delivery = SCAN_DELIVERY_DVB_S; break;
        case SCAN_DVB_C: p_cfg->delivery = SCAN_DELIVERY_DVB_C; break;
        default: p_cfg->delivery = SCAN_DELIVERY_UNKNOWN; break;
    }
    p_cfg->type = p_params->type;
}