#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int /*<<< orphan*/  buff; TYPE_1__ i; } ;
typedef  int Opcode ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 int IAny ; 
#define  IChar 129 
#define  ISet 128 
 int /*<<< orphan*/  ITestSet ; 
 int /*<<< orphan*/  addcharset (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int const,int) ; 
 int charsettype (int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  codechar (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cs_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ getinstr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codecharset (CompileState *compst, const byte *cs, int tt) {
  int c = 0;  /* (=) to avoid warnings */
  Opcode op = charsettype(cs, &c);
  switch (op) {
    case IChar: codechar(compst, c, tt); break;
    case ISet: {  /* non-trivial set? */
      if (tt >= 0 && getinstr(compst, tt).i.code == ITestSet &&
          cs_equal(cs, getinstr(compst, tt + 2).buff))
        addinstruction(compst, IAny, 0);
      else {
        addinstruction(compst, ISet, 0);
        addcharset(compst, cs);
      }
      break;
    }
    default: addinstruction(compst, op, c); break;
  }
}