#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ strip; } ;
struct TYPE_20__ {TYPE_1__* sp; } ;
struct TYPE_19__ {int /*<<< orphan*/  maxstacksize; int /*<<< orphan*/  is_vararg; int /*<<< orphan*/  numparams; int /*<<< orphan*/  lastlinedefined; int /*<<< orphan*/  linedefined; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ SharedProto ;
typedef  TYPE_2__ Proto ;
typedef  TYPE_3__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpByte (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpCode (TYPE_1__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpConstants (TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpDebug (TYPE_1__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpInt (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpProtos (TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpUpvalues (TYPE_1__ const*,TYPE_3__*) ; 

__attribute__((used)) static void DumpFunction (const Proto *fp, TString *psource, DumpState *D) {
  const SharedProto *f = fp->sp;
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
  DumpConstants(fp, D);
  DumpUpvalues(f, D);
  DumpProtos(fp, D);
  DumpDebug(f, D);
}