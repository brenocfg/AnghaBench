#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cbSize; } ;
typedef  TYPE_1__ CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void ME_CopyCharFormat(CHARFORMAT2W *pDest, const CHARFORMAT2W *pSrc)
{
  /* using this with non-2W structs is forbidden */
  assert(pSrc->cbSize == sizeof(CHARFORMAT2W));
  assert(pDest->cbSize == sizeof(CHARFORMAT2W));
  *pDest = *pSrc;
}