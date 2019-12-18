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
typedef  void const uint8_t ;
struct TYPE_3__ {scalar_t__ wire_format_rdata_offset; scalar_t__ wire_format_size; scalar_t__ wire_format; } ;
typedef  TYPE_1__ DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline const void* DNS_RESOURCE_RECORD_RDATA(const DnsResourceRecord *rr) {
        if (!rr)
                return NULL;

        if (!rr->wire_format)
                return NULL;

        assert(rr->wire_format_rdata_offset <= rr->wire_format_size);
        return (uint8_t*) rr->wire_format + rr->wire_format_rdata_offset;
}