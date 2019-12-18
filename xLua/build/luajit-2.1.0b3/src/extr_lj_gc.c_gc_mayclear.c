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
typedef  int /*<<< orphan*/  cTValue ;

/* Variables and functions */
 int /*<<< orphan*/  gcV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_mark_str (int /*<<< orphan*/ ) ; 
 scalar_t__ isfinalized (int /*<<< orphan*/ ) ; 
 scalar_t__ iswhite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisgcv (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisudata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udataV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gc_mayclear(cTValue *o, int val)
{
  if (tvisgcv(o)) {  /* Only collectable objects can be weak references. */
    if (tvisstr(o)) {  /* But strings cannot be used as weak references. */
      gc_mark_str(strV(o));  /* And need to be marked. */
      return 0;
    }
    if (iswhite(gcV(o)))
      return 1;  /* Object is about to be collected. */
    if (tvisudata(o) && val && isfinalized(udataV(o)))
      return 1;  /* Finalized userdata is dropped only from values. */
  }
  return 0;  /* Cannot clear. */
}