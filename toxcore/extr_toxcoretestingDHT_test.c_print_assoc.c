#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  hardening; scalar_t__ ret_timestamp; TYPE_1__ ret_ip_port; scalar_t__ last_pinged; scalar_t__ timestamp; TYPE_1__ ip_port; } ;
typedef  TYPE_1__ IP_Port ;
typedef  TYPE_2__ IPPTsPng ;

/* Variables and functions */
 char* ip_ntoa (int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hardening (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_assoc(IPPTsPng *assoc, uint8_t ours)
{
    IP_Port *ipp = &assoc->ip_port;
    printf("\nIP: %s Port: %u", ip_ntoa(&ipp->ip), ntohs(ipp->port));
    printf("\nTimestamp: %llu", (long long unsigned int) assoc->timestamp);
    printf("\nLast pinged: %llu\n", (long long unsigned int) assoc->last_pinged);

    ipp = &assoc->ret_ip_port;

    if (ours)
        printf("OUR IP: %s Port: %u\n", ip_ntoa(&ipp->ip), ntohs(ipp->port));
    else
        printf("RET IP: %s Port: %u\n", ip_ntoa(&ipp->ip), ntohs(ipp->port));

    printf("Timestamp: %llu\n", (long long unsigned int) assoc->ret_timestamp);
    print_hardening(&assoc->hardening);

}