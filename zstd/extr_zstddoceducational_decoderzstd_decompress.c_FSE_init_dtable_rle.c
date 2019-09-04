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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ accuracy_log; scalar_t__* new_state_base; scalar_t__* num_bits; int /*<<< orphan*/ * symbols; } ;
typedef  TYPE_1__ FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ALLOC () ; 
 void* malloc (int) ; 

__attribute__((used)) static void FSE_init_dtable_rle(FSE_dtable *const dtable, const u8 symb) {
    dtable->symbols = malloc(sizeof(u8));
    dtable->num_bits = malloc(sizeof(u8));
    dtable->new_state_base = malloc(sizeof(u16));

    if (!dtable->symbols || !dtable->num_bits || !dtable->new_state_base) {
        BAD_ALLOC();
    }

    // This setup will always have a state of 0, always return symbol `symb`,
    // and never consume any bits
    dtable->symbols[0] = symb;
    dtable->num_bits[0] = 0;
    dtable->new_state_base[0] = 0;
    dtable->accuracy_log = 0;
}