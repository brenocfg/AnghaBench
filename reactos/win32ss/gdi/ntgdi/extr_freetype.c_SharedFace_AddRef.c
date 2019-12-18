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
struct TYPE_3__ {int /*<<< orphan*/  RefCount; } ;
typedef  TYPE_1__* PSHARED_FACE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_FREETYPE_LOCK_HELD () ; 

__attribute__((used)) static void
SharedFace_AddRef(PSHARED_FACE Ptr)
{
    ASSERT_FREETYPE_LOCK_HELD();

    ++Ptr->RefCount;
}