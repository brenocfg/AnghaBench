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
struct TYPE_4__ {int /*<<< orphan*/  new_state_base; int /*<<< orphan*/  num_bits; int /*<<< orphan*/  symbols; } ;
typedef  TYPE_1__ FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void FSE_free_dtable(FSE_dtable *const dtable) {
    free(dtable->symbols);
    free(dtable->num_bits);
    free(dtable->new_state_base);
    memset(dtable, 0, sizeof(FSE_dtable));
}