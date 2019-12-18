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
typedef  int /*<<< orphan*/  DnsServerFeatureLevel ;

/* Variables and functions */
 scalar_t__ DNS_SERVER_FEATURE_LEVEL_IS_TLS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t dns_port_for_feature_level(DnsServerFeatureLevel level) {
        return DNS_SERVER_FEATURE_LEVEL_IS_TLS(level) ? 853 : 53;
}