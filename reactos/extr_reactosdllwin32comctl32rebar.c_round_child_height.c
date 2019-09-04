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
struct TYPE_3__ {int cyIntegral; int cyMinChild; int /*<<< orphan*/  cyMaxChild; } ;
typedef  TYPE_1__ REBAR_BAND ;

/* Variables and functions */
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int round_child_height(const REBAR_BAND *lpBand, int cyHeight)
{
    int cy = 0;
    if (lpBand->cyIntegral == 0)
        return cyHeight;
    cy = max(cyHeight - (int)lpBand->cyMinChild, 0);
    cy = lpBand->cyMinChild + (cy/lpBand->cyIntegral) * lpBand->cyIntegral;
    cy = min(cy, lpBand->cyMaxChild);
    return cy;
}