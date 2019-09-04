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
struct TYPE_2__ {struct Ziphuft* t; } ;
struct Ziphuft {TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  HFDI ;

/* Variables and functions */
 int /*<<< orphan*/  PFDI_FREE (int /*<<< orphan*/ ,struct Ziphuft*) ; 

__attribute__((used)) static void fdi_Ziphuft_free(HFDI hfdi, struct Ziphuft *t)
{
  register struct Ziphuft *p, *q;

  /* Go through linked list, freeing from the allocated (t[-1]) address. */
  p = t;
  while (p != NULL)
  {
    q = (--p)->v.t;
    PFDI_FREE(hfdi, p);
    p = q;
  }
}