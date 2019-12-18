#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int NameOffset; } ;
struct TYPE_8__ {TYPE_2__ typelib_header; TYPE_1__* typelib; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ctl2_alloc_name (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_name(msft_typelib_t *typelib)
{
    int offset;

    offset = ctl2_alloc_name(typelib, typelib->typelib->name);
    if (offset == -1) return;
    typelib->typelib_header.NameOffset = offset;
    return;
}