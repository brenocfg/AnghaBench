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

/* Variables and functions */
 int /*<<< orphan*/  arg_generators ; 
 int /*<<< orphan*/  arg_man ; 
 int /*<<< orphan*/  arg_scope ; 
 int /*<<< orphan*/  strv_skip (char**,int) ; 
 int verify_units (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_verify(int argc, char *argv[], void *userdata) {
        return verify_units(strv_skip(argv, 1), arg_scope, arg_man, arg_generators);
}