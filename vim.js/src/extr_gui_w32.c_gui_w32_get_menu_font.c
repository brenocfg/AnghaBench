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
struct TYPE_3__ {int cbSize; int /*<<< orphan*/  lfMenuFont; } ;
typedef  TYPE_1__ NONCLIENTMETRICS ;
typedef  int /*<<< orphan*/  LOGFONT ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  SPI_GETNONCLIENTMETRICS ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gui_w32_get_menu_font(LOGFONT *lf)
{
    NONCLIENTMETRICS nm;

    nm.cbSize = sizeof(NONCLIENTMETRICS);
    if (!SystemParametersInfo(
	    SPI_GETNONCLIENTMETRICS,
	    sizeof(NONCLIENTMETRICS),
	    &nm,
	    0))
	return FAIL;
    *lf = nm.lfMenuFont;
    return OK;
}