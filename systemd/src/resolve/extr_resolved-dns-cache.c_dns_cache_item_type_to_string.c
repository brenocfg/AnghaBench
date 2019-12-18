#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/  rcode; } ;
typedef  TYPE_1__ DnsCacheItem ;

/* Variables and functions */
#define  DNS_CACHE_NODATA 131 
#define  DNS_CACHE_NXDOMAIN 130 
#define  DNS_CACHE_POSITIVE 129 
#define  DNS_CACHE_RCODE 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char const* dns_rcode_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *dns_cache_item_type_to_string(DnsCacheItem *item) {
        assert(item);

        switch (item->type) {

        case DNS_CACHE_POSITIVE:
                return "POSITIVE";

        case DNS_CACHE_NODATA:
                return "NODATA";

        case DNS_CACHE_NXDOMAIN:
                return "NXDOMAIN";

        case DNS_CACHE_RCODE:
                return dns_rcode_to_string(item->rcode);
        }

        return NULL;
}