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
struct plain_hashmap_entry {void* value; } ;
struct hashmap_base_entry {scalar_t__ key; } ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ HashmapBase ;

/* Variables and functions */
#define  HASHMAP_TYPE_ORDERED 130 
#define  HASHMAP_TYPE_PLAIN 129 
#define  HASHMAP_TYPE_SET 128 
 int /*<<< orphan*/  assert_not_reached (char*) ; 

__attribute__((used)) static void *entry_value(HashmapBase *h, struct hashmap_base_entry *e) {
        switch (h->type) {

        case HASHMAP_TYPE_PLAIN:
        case HASHMAP_TYPE_ORDERED:
                return ((struct plain_hashmap_entry*)e)->value;

        case HASHMAP_TYPE_SET:
                return (void*) e->key;

        default:
                assert_not_reached("Unknown hashmap type");
        }
}