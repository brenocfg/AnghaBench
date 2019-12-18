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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  Name; scalar_t__ PageCount; int /*<<< orphan*/  Allocated; } ;
typedef  TYPE_1__* PEMS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID FreeHandle(PEMS_HANDLE HandleEntry)
{
    HandleEntry->Allocated = FALSE;
    HandleEntry->PageCount = 0;
    RtlZeroMemory(HandleEntry->Name, sizeof(HandleEntry->Name));
    // InitializeListHead(&HandleEntry->PageList);
}