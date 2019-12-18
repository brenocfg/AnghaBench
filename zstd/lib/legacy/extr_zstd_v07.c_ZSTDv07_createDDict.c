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
struct TYPE_3__ {int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ZSTDv07_customMem ;
typedef  int /*<<< orphan*/  ZSTDv07_DDict ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTDv07_createDDict_advanced (void const*,size_t,TYPE_1__ const) ; 

ZSTDv07_DDict* ZSTDv07_createDDict(const void* dict, size_t dictSize)
{
    ZSTDv07_customMem const allocator = { NULL, NULL, NULL };
    return ZSTDv07_createDDict_advanced(dict, dictSize, allocator);
}