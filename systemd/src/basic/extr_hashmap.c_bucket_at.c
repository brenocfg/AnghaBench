#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct hashmap_base_entry {int dummy; } ;
struct TYPE_6__ {unsigned int entry_size; } ;
struct TYPE_5__ {size_t type; } ;
typedef  TYPE_1__ HashmapBase ;

/* Variables and functions */
 TYPE_3__* hashmap_type_info ; 
 scalar_t__ storage_ptr (TYPE_1__*) ; 

__attribute__((used)) static struct hashmap_base_entry *bucket_at(HashmapBase *h, unsigned idx) {
        return (struct hashmap_base_entry*)
                ((uint8_t*) storage_ptr(h) + idx * hashmap_type_info[h->type].entry_size);
}