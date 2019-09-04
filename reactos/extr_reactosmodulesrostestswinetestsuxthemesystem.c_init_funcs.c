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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pBeginBufferedPaint ; 
 void* pBufferedPaintClear ; 
 void* pEndBufferedPaint ; 
 void* pGetBufferedPaintBits ; 
 void* pGetBufferedPaintDC ; 
 void* pGetBufferedPaintTargetDC ; 
 void* pGetBufferedPaintTargetRect ; 
 void* pOpenThemeDataEx ; 

__attribute__((used)) static void init_funcs(void)
{
    HMODULE hUxtheme = GetModuleHandleA("uxtheme.dll");

#define UXTHEME_GET_PROC(func) p ## func = (void*)GetProcAddress(hUxtheme, #func)
    UXTHEME_GET_PROC(BeginBufferedPaint);
    UXTHEME_GET_PROC(BufferedPaintClear);
    UXTHEME_GET_PROC(EndBufferedPaint);
    UXTHEME_GET_PROC(GetBufferedPaintBits);
    UXTHEME_GET_PROC(GetBufferedPaintDC);
    UXTHEME_GET_PROC(GetBufferedPaintTargetDC);
    UXTHEME_GET_PROC(GetBufferedPaintTargetRect);
    UXTHEME_GET_PROC(BufferedPaintClear);

    UXTHEME_GET_PROC(OpenThemeDataEx);
#undef UXTHEME_GET_PROC
}