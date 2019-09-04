#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__* ResponsePtr ;
typedef  int /*<<< orphan*/  Response ;

/* Variables and functions */
 int /*<<< orphan*/  InitLineList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ (int) ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 

ResponsePtr
InitResponse(void)
{
	ResponsePtr rp;

	rp = (ResponsePtr) calloc(SZ(1), sizeof(Response));
	if (rp != NULL)
		InitLineList(&rp->msg);
	return (rp);
}