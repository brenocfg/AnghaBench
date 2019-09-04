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
struct TYPE_3__ {scalar_t__ typeMask; } ;
typedef  TYPE_1__ VdbeSorter ;
typedef  int /*<<< orphan*/  SorterCompare ;

/* Variables and functions */
 scalar_t__ SORTER_TYPE_INTEGER ; 
 scalar_t__ SORTER_TYPE_TEXT ; 
 int /*<<< orphan*/  vdbeSorterCompare ; 
 int /*<<< orphan*/  vdbeSorterCompareInt ; 
 int /*<<< orphan*/  vdbeSorterCompareText ; 

__attribute__((used)) static SorterCompare vdbeSorterGetCompare(VdbeSorter *p){
  if( p->typeMask==SORTER_TYPE_INTEGER ){
    return vdbeSorterCompareInt;
  }else if( p->typeMask==SORTER_TYPE_TEXT ){
    return vdbeSorterCompareText; 
  }
  return vdbeSorterCompare;
}