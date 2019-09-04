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
#define  CLUSTERMSG_TYPE_FAIL 137 
#define  CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK 136 
#define  CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST 135 
#define  CLUSTERMSG_TYPE_MEET 134 
#define  CLUSTERMSG_TYPE_MFSTART 133 
#define  CLUSTERMSG_TYPE_MODULE 132 
#define  CLUSTERMSG_TYPE_PING 131 
#define  CLUSTERMSG_TYPE_PONG 130 
#define  CLUSTERMSG_TYPE_PUBLISH 129 
#define  CLUSTERMSG_TYPE_UPDATE 128 

const char *clusterGetMessageTypeString(int type) {
    switch(type) {
    case CLUSTERMSG_TYPE_PING: return "ping";
    case CLUSTERMSG_TYPE_PONG: return "pong";
    case CLUSTERMSG_TYPE_MEET: return "meet";
    case CLUSTERMSG_TYPE_FAIL: return "fail";
    case CLUSTERMSG_TYPE_PUBLISH: return "publish";
    case CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST: return "auth-req";
    case CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK: return "auth-ack";
    case CLUSTERMSG_TYPE_UPDATE: return "update";
    case CLUSTERMSG_TYPE_MFSTART: return "mfstart";
    case CLUSTERMSG_TYPE_MODULE: return "module";
    }
    return "unknown";
}