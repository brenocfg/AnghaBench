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
struct skiptags_sys_t {int /*<<< orphan*/  p_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct skiptags_sys_t*) ; 

__attribute__((used)) static void skiptags_sys_Delete(struct skiptags_sys_t *sys)
{
    block_ChainRelease(sys->p_tags);
    free(sys);
}