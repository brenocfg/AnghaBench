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
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetBValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetGValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline COLORREF aa_colorref( COLORREF dst, COLORREF text, BYTE glyph )
{
    COLORREF ret;

    ret = RGB( aa_comp( GetRValue(dst), GetRValue(text), glyph ),
               aa_comp( GetGValue(dst), GetGValue(text), glyph ),
               aa_comp( GetBValue(dst), GetBValue(text), glyph ) );
    return ret;
}