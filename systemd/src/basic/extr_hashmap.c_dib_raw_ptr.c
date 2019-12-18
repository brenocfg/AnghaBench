#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  dib_raw_t ;
struct TYPE_7__ {int entry_size; } ;
struct TYPE_6__ {size_t type; } ;
typedef  TYPE_1__ HashmapBase ;

/* Variables and functions */
 TYPE_4__* hashmap_type_info ; 
 int n_buckets (TYPE_1__*) ; 
 scalar_t__ storage_ptr (TYPE_1__*) ; 

__attribute__((used)) static dib_raw_t *dib_raw_ptr(HashmapBase *h) {
        return (dib_raw_t*)
                ((uint8_t*) storage_ptr(h) + hashmap_type_info[h->type].entry_size * n_buckets(h));
}