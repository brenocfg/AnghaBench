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
struct TYPE_3__ {scalar_t__ uNumBands; int /*<<< orphan*/  bands; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  REBAR_BAND ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/ * DPA_GetPtr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline REBAR_BAND* REBAR_GetBand(const REBAR_INFO *infoPtr, INT i)
{
    assert(i >= 0 && i < infoPtr->uNumBands);
    return DPA_GetPtr(infoPtr->bands, i);
}