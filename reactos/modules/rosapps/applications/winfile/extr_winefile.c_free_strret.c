#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  iMalloc; } ;
struct TYPE_4__ {scalar_t__ uType; int /*<<< orphan*/  (* UNION_MEMBER ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ STRRET ;

/* Variables and functions */
 TYPE_3__ Globals ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STRRET_WSTR ; 
 int /*<<< orphan*/  pOleStr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_strret(STRRET* str)
{
	if (str->uType == STRRET_WSTR)
		IMalloc_Free(Globals.iMalloc, str->UNION_MEMBER(pOleStr));
}