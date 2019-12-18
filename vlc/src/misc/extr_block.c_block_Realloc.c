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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * block_TryRealloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

block_t *block_Realloc (block_t *block, ssize_t prebody, size_t body)
{
    block_t *rea = block_TryRealloc (block, prebody, body);
    if (rea == NULL)
        block_Release(block);
    return rea;
}