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
typedef  int /*<<< orphan*/  CPpmd8 ;

/* Variables and functions */
 int /*<<< orphan*/  InsertNode (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U2I (unsigned int) ; 

__attribute__((used)) static void FreeUnits(CPpmd8 *p, void *ptr, unsigned nu)
{
  InsertNode(p, ptr, U2I(nu));
}