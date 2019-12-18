#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* key; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  class; } ;
typedef  TYPE_2__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_CACHE_FLUSH (int /*<<< orphan*/ ) ; 
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DNS_RESOURCE_RECORD_RDATA (TYPE_2__*) ; 
 int /*<<< orphan*/  DNS_RESOURCE_RECORD_RDATA_SIZE (TYPE_2__*) ; 
 size_t MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int dns_resource_record_to_wire_format (TYPE_2__*,int) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int mdns_rr_compare(DnsResourceRecord * const *a, DnsResourceRecord * const *b) {
        DnsResourceRecord *x = *(DnsResourceRecord **) a, *y = *(DnsResourceRecord **) b;
        size_t m;
        int r;

        assert(x);
        assert(y);

        r = CMP(CLEAR_CACHE_FLUSH(x->key->class), CLEAR_CACHE_FLUSH(y->key->class));
        if (r != 0)
                return r;

        r = CMP(x->key->type, y->key->type);
        if (r != 0)
                return r;

        r = dns_resource_record_to_wire_format(x, false);
        if (r < 0) {
                log_warning_errno(r, "Can't wire-format RR: %m");
                return 0;
        }

        r = dns_resource_record_to_wire_format(y, false);
        if (r < 0) {
                log_warning_errno(r, "Can't wire-format RR: %m");
                return 0;
        }

        m = MIN(DNS_RESOURCE_RECORD_RDATA_SIZE(x), DNS_RESOURCE_RECORD_RDATA_SIZE(y));

        r = memcmp(DNS_RESOURCE_RECORD_RDATA(x), DNS_RESOURCE_RECORD_RDATA(y), m);
        if (r != 0)
                return r;

        return CMP(DNS_RESOURCE_RECORD_RDATA_SIZE(x), DNS_RESOURCE_RECORD_RDATA_SIZE(y));
}