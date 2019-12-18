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
typedef  int uint16_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
#define  DNS_TYPE_A 130 
#define  DNS_TYPE_AAAA 129 
#define  DNS_TYPE_ANY 128 
 int EINVAL ; 

int dns_type_to_af(uint16_t t) {
        switch (t) {

        case DNS_TYPE_A:
                return AF_INET;

        case DNS_TYPE_AAAA:
                return AF_INET6;

        case DNS_TYPE_ANY:
                return AF_UNSPEC;

        default:
                return -EINVAL;
        }
}