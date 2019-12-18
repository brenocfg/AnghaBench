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
typedef  int /*<<< orphan*/  strm_value ;

/* Variables and functions */
 scalar_t__ ELEM_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELEM_SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_value
quick_select(strm_value arr[], int n)
{
  int low, high;
  int median;
  int middle, ll, hh;

  low = 0; high = n-1; median = (low + high) / 2;
  for (;;) {
    if (high <= low) /* One element only */
      return arr[median];

    if (high == low + 1) {  /* Two elements only */
      if (ELEM_GT(arr[low],arr[high]))
        ELEM_SWAP(arr[low], arr[high]);
      return arr[median];
    }

    /* Find median of low, middle and high items; swap into position low */
    middle = (low + high) / 2;
    if (ELEM_GT(arr[middle], arr[high])) ELEM_SWAP(arr[middle], arr[high]);
    if (ELEM_GT(arr[low], arr[high]))    ELEM_SWAP(arr[low], arr[high]);
    if (ELEM_GT(arr[middle], arr[low]))  ELEM_SWAP(arr[middle], arr[low]);

    /* Swap low item (now in position middle) into position (low+1) */
    ELEM_SWAP(arr[middle], arr[low+1]);

    /* Nibble from each end towards middle, swapping items when stuck */
    ll = low + 1;
    hh = high;
    for (;;) {
      do ll++; while (ELEM_GT(arr[low], arr[ll]));
      do hh--; while (ELEM_GT(arr[hh], arr[low]));

      if (hh < ll)
        break;

      ELEM_SWAP(arr[ll], arr[hh]);
    }

    /* Swap middle item (in position low) back into correct position */
    ELEM_SWAP(arr[low], arr[hh]);

    /* Re-set active partition */
    if (hh <= median)
      low = ll;
    if (hh >= median)
      high = hh - 1;
  }
}