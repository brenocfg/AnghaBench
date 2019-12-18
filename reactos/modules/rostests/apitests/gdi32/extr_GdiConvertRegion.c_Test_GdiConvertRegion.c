#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ HRGN ;

/* Variables and functions */
 scalar_t__ GdiConvertRegion (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_GdiConvertRegion()
{
    ok(GdiConvertRegion((HRGN)-1) == (HRGN)-1, "\n");
    ok(GdiConvertRegion((HRGN)0) == (HRGN)0, "\n");
    ok(GdiConvertRegion((HRGN)1) == (HRGN)1, "\n");
    ok(GdiConvertRegion((HRGN)2) == (HRGN)2, "\n");
}