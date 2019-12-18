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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_sd_delete_common( input_item_t **pp_item )
{
    assert(pp_item != NULL);

    input_item_t *p_item = *pp_item;
    if (p_item != NULL) /* item may be NULL if already removed earlier */
        input_item_Release( p_item );

    return 1;
}