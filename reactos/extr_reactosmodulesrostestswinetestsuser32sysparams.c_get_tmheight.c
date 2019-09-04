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
struct TYPE_3__ {int tmHeight; int /*<<< orphan*/  tmExternalLeading; } ;
typedef  TYPE_1__ TEXTMETRICA ;
typedef  int /*<<< orphan*/  LOGFONTA ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFontIndirectA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTextMetricsA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdc ; 

__attribute__((used)) static int get_tmheight( LOGFONTA *plf, int flag)
{
    TEXTMETRICA tm;
    HFONT hfont = CreateFontIndirectA( plf);
    hfont = SelectObject( hdc, hfont);
    GetTextMetricsA( hdc, &tm);
    hfont = SelectObject( hdc, hfont);
    return tm.tmHeight + (flag ? tm.tmExternalLeading : 0);
}