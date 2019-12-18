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
typedef  size_t elem_type_t ;
struct TYPE_2__ {scalar_t__ dispiid; int /*<<< orphan*/  iids; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 size_t ET_A ; 
 int /*<<< orphan*/  _test_disp (unsigned int,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  _test_elem_tag (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _test_ifaces (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* elem_type_infos ; 

__attribute__((used)) static void _test_elem_type(unsigned line, IUnknown *unk, elem_type_t type)
{
    _test_elem_tag(line, unk, elem_type_infos[type].tag);
    _test_ifaces(line, unk, elem_type_infos[type].iids);

    if(elem_type_infos[type].dispiid && type != ET_A)
        _test_disp(line, unk, elem_type_infos[type].dispiid, "[object]");
}