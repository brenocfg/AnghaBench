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
typedef  int /*<<< orphan*/  TTree ;
typedef  int /*<<< orphan*/  CompileState ;
typedef  int /*<<< orphan*/  Charset ;

/* Variables and functions */
 int NOINST ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fixedlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fullset ; 
 int /*<<< orphan*/  getfirst (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ needfollow (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int codeseq1 (CompileState *compst, TTree *p1, TTree *p2,
                     int tt, const Charset *fl) {
  if (needfollow(p1)) {
    Charset fl1;
    getfirst(p2, fl, &fl1);  /* p1 follow is p2 first */
    codegen(compst, p1, 0, tt, &fl1);
  }
  else  /* use 'fullset' as follow */
    codegen(compst, p1, 0, tt, fullset);
  if (fixedlen(p1) != 0)  /* can 'p1' consume anything? */
    return  NOINST;  /* invalidate test */
  else return tt;  /* else 'tt' still protects sib2 */
}