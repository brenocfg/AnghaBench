#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* header; } ;
typedef  TYPE_2__ sd_bus_message ;
struct TYPE_11__ {scalar_t__ message_version; scalar_t__ message_endian; } ;
typedef  TYPE_3__ sd_bus ;
struct TYPE_9__ {scalar_t__ version; scalar_t__ endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int bus_message_remarshal (TYPE_3__*,TYPE_2__**) ; 

__attribute__((used)) static int bus_remarshal_message(sd_bus *b, sd_bus_message **m) {
        bool remarshal = false;

        assert(b);

        /* wrong packet version */
        if (b->message_version != 0 && b->message_version != (*m)->header->version)
                remarshal = true;

        /* wrong packet endianness */
        if (b->message_endian != 0 && b->message_endian != (*m)->header->endian)
                remarshal = true;

        return remarshal ? bus_message_remarshal(b, m) : 0;
}