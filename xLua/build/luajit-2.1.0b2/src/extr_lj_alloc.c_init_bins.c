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
typedef  TYPE_1__* sbinptr ;
typedef  int /*<<< orphan*/  mstate ;
typedef  scalar_t__ bindex_t ;
struct TYPE_3__ {struct TYPE_3__* bk; struct TYPE_3__* fd; } ;

/* Variables and functions */
 scalar_t__ NSMALLBINS ; 
 TYPE_1__* smallbin_at (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void init_bins(mstate m)
{
  /* Establish circular links for smallbins */
  bindex_t i;
  for (i = 0; i < NSMALLBINS; i++) {
    sbinptr bin = smallbin_at(m,i);
    bin->fd = bin->bk = bin;
  }
}