#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ctypeid; } ;
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ CType ;
typedef  int /*<<< orphan*/  CTState ;

/* Variables and functions */
 TYPE_4__* cdataV (int /*<<< orphan*/ *) ; 
 scalar_t__ ctype_isrefarray (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_isstruct (int /*<<< orphan*/ ) ; 
 TYPE_1__* lj_ctype_rawref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 

int lj_cconv_multi_init(CTState *cts, CType *d, TValue *o)
{
  if (!(ctype_isrefarray(d->info) || ctype_isstruct(d->info)))
    return 0;  /* Destination is not an aggregate. */
  if (tvistab(o) || (tvisstr(o) && !ctype_isstruct(d->info)))
    return 0;  /* Initializer is not a value. */
  if (tviscdata(o) && lj_ctype_rawref(cts, cdataV(o)->ctypeid) == d)
    return 0;  /* Source and destination are identical aggregates. */
  return 1;  /* Otherwise the initializer is a value. */
}