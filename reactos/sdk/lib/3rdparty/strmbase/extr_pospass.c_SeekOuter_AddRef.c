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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  IUnknown_inner; int /*<<< orphan*/ * outer_unk; scalar_t__ bUnkOuterValid; } ;
typedef  TYPE_1__ PassThruImpl ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ULONG SeekOuter_AddRef(PassThruImpl *This)
{
    if (This->outer_unk && This->bUnkOuterValid)
        return IUnknown_AddRef(This->outer_unk);
    return IUnknown_AddRef(&This->IUnknown_inner);
}