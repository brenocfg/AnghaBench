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
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/ * TAKE_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int hashmap_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hashmap_complete_move(Hashmap **s, Hashmap **other) {
        assert(s);
        assert(other);

        if (!*other)
                return 0;

        if (*s)
                return hashmap_move(*s, *other);
        else
                *s = TAKE_PTR(*other);

        return 0;
}