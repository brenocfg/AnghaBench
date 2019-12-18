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
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/ * Sizes; int /*<<< orphan*/ * Offsets; } ;
typedef  TYPE_1__ _cmsDICelem ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void FreeElem(cmsContext ContextID, _cmsDICelem* e)
{
    if (e ->Offsets != NULL)  _cmsFree(ContextID, e -> Offsets);
    if (e ->Sizes   != NULL)  _cmsFree(ContextID, e -> Sizes);
    e->Offsets = e ->Sizes = NULL;
}