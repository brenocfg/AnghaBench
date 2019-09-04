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
struct TYPE_3__ {char const* abbrev; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ LOCALECONV ;

/* Variables and functions */
 int lstrcmpiA (char const*,int /*<<< orphan*/ ) ; 

const char* __ConvertName(const char* lname, LOCALECONV* ConvTable, int TableSize) {
  int i;
  int cmp;
  int low = 0;
  int high = TableSize - 1;

  /*  typical binary search - do until no more to search or match */
  while (low <= high) {
    i = (low + high) / 2;

    if ((cmp = lstrcmpiA(lname, (*(ConvTable + i)).name)) == 0)
      return (*(ConvTable + i)).abbrev;
    else if (cmp < 0)
      high = i - 1;
    else
      low = i + 1;
  }
  return lname;
}