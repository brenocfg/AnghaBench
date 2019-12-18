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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ GdiDeleteLocalDC (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_GdiDeleteLocalDC()
{
    ok(GdiDeleteLocalDC((HDC)-1) == TRUE, "\n");
    ok(GdiDeleteLocalDC((HDC)0) == TRUE, "\n");
    ok(GdiDeleteLocalDC((HDC)1) == TRUE, "\n");
    ok(GdiDeleteLocalDC((HDC)2) == TRUE, "\n");
}