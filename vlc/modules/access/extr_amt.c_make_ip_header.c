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
struct TYPE_3__ {int ver_ihl; int tos; int id; int frag_off; int ttl; int protocol; int options; int /*<<< orphan*/  srcAddr; scalar_t__ check; int /*<<< orphan*/  tot_len; } ;
typedef  TYPE_1__ amt_ip_alert_t ;

/* Variables and functions */
 scalar_t__ IGMP_REPORT_LEN ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ IP_HDR_IGMP_LEN ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 

__attribute__((used)) static void make_ip_header( amt_ip_alert_t *p_ipHead )
{
    p_ipHead->ver_ihl = 0x46;
    p_ipHead->tos = 0xc0;
    p_ipHead->tot_len = htons( IP_HDR_IGMP_LEN + IGMP_REPORT_LEN );
    p_ipHead->id = 0x00;
    p_ipHead->frag_off = 0x0000;
    p_ipHead->ttl = 0x01;
    p_ipHead->protocol = 0x02;
    p_ipHead->check = 0;
    p_ipHead->srcAddr = INADDR_ANY;
    p_ipHead->options = 0x0000;
}