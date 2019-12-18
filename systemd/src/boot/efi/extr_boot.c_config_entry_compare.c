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
typedef  scalar_t__ UINTN ;
struct TYPE_4__ {scalar_t__ tries_left; scalar_t__ tries_done; int /*<<< orphan*/  id; } ;
typedef  int INTN ;
typedef  TYPE_1__ ConfigEntry ;

/* Variables and functions */
 int str_verscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INTN config_entry_compare(ConfigEntry *a, ConfigEntry *b) {
        INTN r;

        /* Order entries that have no tries left to the end of the list */
        if (a->tries_left != 0 && b->tries_left == 0)
                return -1;
        if (a->tries_left == 0 && b->tries_left != 0)
                return 1;

        r = str_verscmp(a->id, b->id);
        if (r != 0)
                return r;

        if (a->tries_left == (UINTN) -1 ||
            b->tries_left == (UINTN) -1)
                return 0;

        /* If both items have boot counting, and otherwise are identical, put the entry with more tries left first */
        if (a->tries_left > b->tries_left)
                return -1;
        if (a->tries_left < b->tries_left)
                return 1;

        /* If they have the same number of tries left, then let the one win which was tried fewer times so far */
        if (a->tries_done < b->tries_done)
                return -1;
        if (a->tries_done > b->tries_done)
                return 1;

        return 0;
}