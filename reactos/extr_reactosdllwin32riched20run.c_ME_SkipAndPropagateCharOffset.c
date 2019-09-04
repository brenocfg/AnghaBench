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
typedef  int /*<<< orphan*/  ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/ * ME_FindItemFwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_PropagateCharOffset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diRunOrParagraphOrEnd ; 

void ME_SkipAndPropagateCharOffset(ME_DisplayItem *p, int shift)
{
  p = ME_FindItemFwd(p, diRunOrParagraphOrEnd);
  assert(p);
  ME_PropagateCharOffset(p, shift);
}