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
typedef  int U32 ;
struct TYPE_3__ {int num; int size; } ;
typedef  TYPE_1__ COVER_epoch_info_t ;

/* Variables and functions */
 int MAX (int,int) ; 
 int MIN (int const,int) ; 
 int /*<<< orphan*/  assert (int) ; 

COVER_epoch_info_t COVER_computeEpochs(U32 maxDictSize,
                                       U32 nbDmers, U32 k, U32 passes)
{
  const U32 minEpochSize = k * 10;
  COVER_epoch_info_t epochs;
  epochs.num = MAX(1, maxDictSize / k / passes);
  epochs.size = nbDmers / epochs.num;
  if (epochs.size >= minEpochSize) {
      assert(epochs.size * epochs.num <= nbDmers);
      return epochs;
  }
  epochs.size = MIN(minEpochSize, nbDmers);
  epochs.num = nbDmers / epochs.size;
  assert(epochs.size * epochs.num <= nbDmers);
  return epochs;
}