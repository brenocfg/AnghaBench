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
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_array (int /*<<< orphan*/ *) ; 
 scalar_t__ needs_space_after (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_array_is_decl_as_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_is_alias (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_pointer_left(FILE *h, type_t *ref)
{
    if (needs_space_after(ref))
        fprintf(h, " ");
    if (!type_is_alias(ref) && is_array(ref) && !type_array_is_decl_as_ptr(ref))
        fprintf(h, "(");
    fprintf(h, "*");
}