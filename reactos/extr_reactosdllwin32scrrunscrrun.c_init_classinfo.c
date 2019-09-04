#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct provideclassinfo {int /*<<< orphan*/  const* guid; int /*<<< orphan*/ * outer; TYPE_1__ IProvideClassInfo_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  provideclassinfovtbl ; 

void init_classinfo(const GUID *guid, IUnknown *outer, struct provideclassinfo *classinfo)
{
    classinfo->IProvideClassInfo_iface.lpVtbl = &provideclassinfovtbl;
    classinfo->outer = outer;
    classinfo->guid = guid;
}