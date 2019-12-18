#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ strip; } ;
struct TYPE_18__ {int /*<<< orphan*/  maxstacksize; int /*<<< orphan*/  is_vararg; int /*<<< orphan*/  numparams; int /*<<< orphan*/  lastlinedefined; int /*<<< orphan*/  linedefined; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ Proto ;
typedef  TYPE_2__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpByte (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpCode (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpConstants (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpDebug (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpInt (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpProtos (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpUpvalues (TYPE_1__ const*,TYPE_2__*) ; 

__attribute__((used)) static void DumpFunction (const Proto *f, TString *psource, DumpState *D) {
  if (D->strip || f->source == psource)
    DumpString(NULL, D);  /* no debug info or same source as its parent */
  else
    DumpString(f->source, D);
  DumpInt(f->linedefined, D);
  DumpInt(f->lastlinedefined, D);
  DumpByte(f->numparams, D);
  DumpByte(f->is_vararg, D);
  DumpByte(f->maxstacksize, D);
  DumpCode(f, D);
  DumpConstants(f, D);
  DumpUpvalues(f, D);
  DumpProtos(f, D);
  DumpDebug(f, D);
}