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

/* Variables and functions */
#define  SENTINEL_FAILOVER_STATE_NONE 134 
#define  SENTINEL_FAILOVER_STATE_RECONF_SLAVES 133 
#define  SENTINEL_FAILOVER_STATE_SELECT_SLAVE 132 
#define  SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE 131 
#define  SENTINEL_FAILOVER_STATE_UPDATE_CONFIG 130 
#define  SENTINEL_FAILOVER_STATE_WAIT_PROMOTION 129 
#define  SENTINEL_FAILOVER_STATE_WAIT_START 128 

const char *sentinelFailoverStateStr(int state) {
    switch(state) {
    case SENTINEL_FAILOVER_STATE_NONE: return "none";
    case SENTINEL_FAILOVER_STATE_WAIT_START: return "wait_start";
    case SENTINEL_FAILOVER_STATE_SELECT_SLAVE: return "select_slave";
    case SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE: return "send_slaveof_noone";
    case SENTINEL_FAILOVER_STATE_WAIT_PROMOTION: return "wait_promotion";
    case SENTINEL_FAILOVER_STATE_RECONF_SLAVES: return "reconf_slaves";
    case SENTINEL_FAILOVER_STATE_UPDATE_CONFIG: return "update_config";
    default: return "unknown";
    }
}