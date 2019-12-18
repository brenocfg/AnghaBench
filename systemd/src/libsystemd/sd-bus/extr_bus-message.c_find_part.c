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
typedef  int /*<<< orphan*/  uint8_t ;
struct bus_body_part {size_t size; struct bus_body_part* next; scalar_t__ data; } ;
struct TYPE_4__ {size_t cached_rindex_part_begin; struct bus_body_part* cached_rindex_part; struct bus_body_part body; } ;
typedef  TYPE_1__ sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_body_part_map (struct bus_body_part*) ; 

__attribute__((used)) static struct bus_body_part* find_part(sd_bus_message *m, size_t index, size_t sz, void **p) {
        struct bus_body_part *part;
        size_t begin;
        int r;

        assert(m);

        if (m->cached_rindex_part && index >= m->cached_rindex_part_begin) {
                part = m->cached_rindex_part;
                begin = m->cached_rindex_part_begin;
        } else {
                part = &m->body;
                begin = 0;
        }

        while (part) {
                if (index < begin)
                        return NULL;

                if (index + sz <= begin + part->size) {

                        r = bus_body_part_map(part);
                        if (r < 0)
                                return NULL;

                        if (p)
                                *p = (uint8_t*) part->data + index - begin;

                        m->cached_rindex_part = part;
                        m->cached_rindex_part_begin = begin;

                        return part;
                }

                begin += part->size;
                part = part->next;
        }

        return NULL;
}