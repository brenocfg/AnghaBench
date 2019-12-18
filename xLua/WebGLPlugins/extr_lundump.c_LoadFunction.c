#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* maxstacksize; void* is_vararg; void* numparams; void* lastlinedefined; void* linedefined; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  LoadState ;

/* Variables and functions */
 void* LoadByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadCode (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadConstants (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadDebug (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* LoadInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadProtos (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * LoadString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadUpvalues (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void LoadFunction (LoadState *S, Proto *f, TString *psource) {
  f->source = LoadString(S);
  if (f->source == NULL)  /* no source in dump? */
    f->source = psource;  /* reuse parent's source */
  f->linedefined = LoadInt(S);
  f->lastlinedefined = LoadInt(S);
  f->numparams = LoadByte(S);
  f->is_vararg = LoadByte(S);
  f->maxstacksize = LoadByte(S);
  LoadCode(S, f);
  LoadConstants(S, f);
  LoadUpvalues(S, f);
  LoadProtos(S, f);
  LoadDebug(S, f);
}