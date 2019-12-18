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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DNODE_MUST_BE_ALLOCATED ; 
 int dnode_hold_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

int
dnode_hold(objset_t *os, uint64_t object, void *tag, dnode_t **dnp)
{
	return (dnode_hold_impl(os, object, DNODE_MUST_BE_ALLOCATED, 0, tag,
	    dnp));
}