#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  match_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ag_realloc (int /*<<< orphan*/ *,size_t) ; 

void realloc_matches(match_t **matches, size_t *matches_size, size_t matches_len) {
    if (matches_len < *matches_size) {
        return;
    }
    /* TODO: benchmark initial size of matches. 100 may be too small/big */
    *matches_size = *matches ? *matches_size * 2 : 100;
    *matches = ag_realloc(*matches, *matches_size * sizeof(match_t));
}