#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bus_header {int dummy; } ;
struct TYPE_5__ {void* name; } ;
struct TYPE_6__ {int poisoned; int fields_size; int free_header; scalar_t__ n_header_offsets; size_t* header_offsets; void* header; TYPE_1__ error; void* sender; void* destination; void* member; void* interface; void* path; } ;
typedef  TYPE_2__ sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN8 (size_t) ; 
 size_t ALIGN_TO (size_t,size_t) ; 
 scalar_t__ ELEMENTSOF (size_t*) ; 
 void* adjust_pointer (void*,void*,size_t,void*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memzero (void*,size_t) ; 
 void* realloc (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *message_extend_fields(sd_bus_message *m, size_t align, size_t sz, bool add_offset) {
        void *op, *np;
        size_t old_size, new_size, start;

        assert(m);

        if (m->poisoned)
                return NULL;

        old_size = sizeof(struct bus_header) + m->fields_size;
        start = ALIGN_TO(old_size, align);
        new_size = start + sz;

        if (new_size < start ||
            new_size > (size_t) ((uint32_t) -1))
                goto poison;

        if (old_size == new_size)
                return (uint8_t*) m->header + old_size;

        if (m->free_header) {
                np = realloc(m->header, ALIGN8(new_size));
                if (!np)
                        goto poison;
        } else {
                /* Initially, the header is allocated as part of
                 * the sd_bus_message itself, let's replace it by
                 * dynamic data */

                np = malloc(ALIGN8(new_size));
                if (!np)
                        goto poison;

                memcpy(np, m->header, sizeof(struct bus_header));
        }

        /* Zero out padding */
        if (start > old_size)
                memzero((uint8_t*) np + old_size, start - old_size);

        op = m->header;
        m->header = np;
        m->fields_size = new_size - sizeof(struct bus_header);

        /* Adjust quick access pointers */
        m->path = adjust_pointer(m->path, op, old_size, m->header);
        m->interface = adjust_pointer(m->interface, op, old_size, m->header);
        m->member = adjust_pointer(m->member, op, old_size, m->header);
        m->destination = adjust_pointer(m->destination, op, old_size, m->header);
        m->sender = adjust_pointer(m->sender, op, old_size, m->header);
        m->error.name = adjust_pointer(m->error.name, op, old_size, m->header);

        m->free_header = true;

        if (add_offset) {
                if (m->n_header_offsets >= ELEMENTSOF(m->header_offsets))
                        goto poison;

                m->header_offsets[m->n_header_offsets++] = new_size - sizeof(struct bus_header);
        }

        return (uint8_t*) np + start;

poison:
        m->poisoned = true;
        return NULL;
}