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
typedef  int /*<<< orphan*/  XLATEOBJ ;
typedef  int /*<<< orphan*/  SURFOBJ ;
typedef  int /*<<< orphan*/  RECTL ;
typedef  int /*<<< orphan*/  CLIPOBJ ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BLENDOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

BOOLEAN
Dummy_AlphaBlend(SURFOBJ* Dest, SURFOBJ* Source, RECTL* DestRect,
                 RECTL* SourceRect, CLIPOBJ* ClipRegion,
                 XLATEOBJ* ColorTranslation, BLENDOBJ* BlendObj)
{
  return FALSE;
}