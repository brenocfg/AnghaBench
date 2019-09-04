#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int Length; int* Buffer; } ;
struct TYPE_5__ {TYPE_1__ PathNameU; } ;
typedef  TYPE_2__* PVFATFCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
vfatFCBIsRoot(
    PVFATFCB FCB)
{
    return FCB->PathNameU.Length == sizeof(WCHAR) && FCB->PathNameU.Buffer[0] == L'\\' ? TRUE : FALSE;
}