#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {size_t accuracy_log; void* new_state_base; void* num_bits; void* symbols; } ;
typedef  TYPE_1__ FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void FSE_copy_dtable(FSE_dtable *const dst, const FSE_dtable *const src) {
    if (src->accuracy_log == 0) {
        memset(dst, 0, sizeof(FSE_dtable));
        return;
    }

    size_t size = (size_t)1 << src->accuracy_log;
    dst->accuracy_log = src->accuracy_log;

    dst->symbols = malloc(size);
    dst->num_bits = malloc(size);
    dst->new_state_base = malloc(size * sizeof(u16));
    if (!dst->symbols || !dst->num_bits || !dst->new_state_base) {
        BAD_ALLOC();
    }

    memcpy(dst->symbols, src->symbols, size);
    memcpy(dst->num_bits, src->num_bits, size);
    memcpy(dst->new_state_base, src->new_state_base, size * sizeof(u16));
}