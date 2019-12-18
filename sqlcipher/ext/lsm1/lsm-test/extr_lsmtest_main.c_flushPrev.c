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
struct TYPE_2__ {scalar_t__ nData; int /*<<< orphan*/  nUs; int /*<<< orphan*/  iOff; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ prev ; 

__attribute__((used)) static void flushPrev(FILE *pOut){
  if( prev.nData ){
    fprintf(pOut, "w %s %lld %d %d\n", "d", prev.iOff, prev.nData, prev.nUs);
    prev.nData = 0;
  }
}