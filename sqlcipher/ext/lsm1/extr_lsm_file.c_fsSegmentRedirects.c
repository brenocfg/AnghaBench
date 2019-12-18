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
struct TYPE_4__ {int /*<<< orphan*/  iLastPg; int /*<<< orphan*/  iRoot; int /*<<< orphan*/  iFirst; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 scalar_t__ fsPageRedirects (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsSegmentRedirects(FileSystem *pFS, Segment *p){
  return (p && (
      fsPageRedirects(pFS, p, p->iFirst)
   || fsPageRedirects(pFS, p, p->iRoot)
   || fsPageRedirects(pFS, p, p->iLastPg)
  ));
}