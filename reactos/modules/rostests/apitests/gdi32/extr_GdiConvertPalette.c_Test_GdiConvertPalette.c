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
typedef  scalar_t__ HPALETTE ;

/* Variables and functions */
 scalar_t__ GdiConvertPalette (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_GdiConvertPalette()
{
    ok(GdiConvertPalette((HPALETTE)-1) == (HPALETTE)-1, "\n");
    ok(GdiConvertPalette((HPALETTE)0) == (HPALETTE)0, "\n");
    ok(GdiConvertPalette((HPALETTE)1) == (HPALETTE)1, "\n");
    ok(GdiConvertPalette((HPALETTE)2) == (HPALETTE)2, "\n");
}