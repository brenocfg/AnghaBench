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
typedef  int /*<<< orphan*/  sd_journal ;

/* Variables and functions */
 scalar_t__ arg_field ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int print_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int print_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int print_entry(sd_journal *j, unsigned n_found, bool verb_is_info) {
        assert(j);

        if (verb_is_info)
                return print_info(stdout, j, n_found);
        else if (arg_field)
                return print_field(stdout, j);
        else
                return print_list(stdout, j, n_found);
}