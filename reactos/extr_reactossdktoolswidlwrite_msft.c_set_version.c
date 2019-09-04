#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_2__* typelib; TYPE_1__ typelib_header; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_6__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_VERSION ; 
 int /*<<< orphan*/  get_attrv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_version(msft_typelib_t *typelib)
{
    typelib->typelib_header.version = get_attrv( typelib->typelib->attrs, ATTR_VERSION );
}