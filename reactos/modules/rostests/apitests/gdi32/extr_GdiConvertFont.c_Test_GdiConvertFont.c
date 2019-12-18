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
typedef  scalar_t__ HFONT ;

/* Variables and functions */
 scalar_t__ GdiConvertFont (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_GdiConvertFont()
{
    ok(GdiConvertFont((HFONT)-1) == (HFONT)-1, "\n");
    ok(GdiConvertFont((HFONT)0) == (HFONT)0, "\n");
    ok(GdiConvertFont((HFONT)1) == (HFONT)1, "\n");
    ok(GdiConvertFont((HFONT)2) == (HFONT)2, "\n");
}