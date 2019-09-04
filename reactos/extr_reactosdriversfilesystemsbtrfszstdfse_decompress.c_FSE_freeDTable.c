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
typedef  int /*<<< orphan*/  FSE_DTable ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 

void FSE_freeDTable (FSE_DTable* dt)
{
    ExFreePool(dt);
}