#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int themeProp; int /*<<< orphan*/  sysColor; } ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 TYPE_1__* EdgeColorMap ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemeColor (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static COLORREF get_edge_color (int edgeType, HTHEME theme, int part, int state)
{
    COLORREF col;
    if ((EdgeColorMap[edgeType].themeProp == -1)
        || FAILED (GetThemeColor (theme, part, state, 
            EdgeColorMap[edgeType].themeProp, &col)))
        col = GetSysColor (EdgeColorMap[edgeType].sysColor);
    return col;
}