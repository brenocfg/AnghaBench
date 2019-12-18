#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entry_size; } ;
struct TYPE_6__ {size_t type; } ;
typedef  TYPE_1__ HashmapBase ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_FREE ; 
 int /*<<< orphan*/  bucket_at (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  bucket_set_dib (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_2__* hashmap_type_info ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bucket_mark_free(HashmapBase *h, unsigned idx) {
        memzero(bucket_at(h, idx), hashmap_type_info[h->type].entry_size);
        bucket_set_dib(h, idx, DIB_FREE);
}