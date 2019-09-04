#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  n; } ;
struct TYPE_16__ {int tag; TYPE_1__ u; } ;
typedef  TYPE_2__ TTree ;
typedef  int /*<<< orphan*/  CompileState ;
typedef  int /*<<< orphan*/  Charset ;

/* Variables and functions */
 int /*<<< orphan*/  IAny ; 
 int /*<<< orphan*/  IFail ; 
#define  TAnd 142 
#define  TAny 141 
#define  TBehind 140 
#define  TCall 139 
#define  TCapture 138 
#define  TChar 137 
#define  TChoice 136 
#define  TFalse 135 
#define  TGrammar 134 
#define  TNot 133 
#define  TRep 132 
#define  TRunTime 131 
#define  TSeq 130 
#define  TSet 129 
#define  TTrue 128 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codeand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codebehind (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  codecall (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  codecapture (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  codechar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codecharset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codechoice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  codegrammar (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  codenot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coderep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  coderuntime (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int codeseq1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sib1 (TYPE_2__*) ; 
 TYPE_2__* sib2 (TYPE_2__*) ; 
 int /*<<< orphan*/  treebuffer (TYPE_2__*) ; 

__attribute__((used)) static void codegen (CompileState *compst, TTree *tree, int opt, int tt,
                     const Charset *fl) {
 tailcall:
  switch (tree->tag) {
    case TChar: codechar(compst, tree->u.n, tt); break;
    case TAny: addinstruction(compst, IAny, 0); break;
    case TSet: codecharset(compst, treebuffer(tree), tt); break;
    case TTrue: break;
    case TFalse: addinstruction(compst, IFail, 0); break;
    case TChoice: codechoice(compst, sib1(tree), sib2(tree), opt, fl); break;
    case TRep: coderep(compst, sib1(tree), opt, fl); break;
    case TBehind: codebehind(compst, tree); break;
    case TNot: codenot(compst, sib1(tree)); break;
    case TAnd: codeand(compst, sib1(tree), tt); break;
    case TCapture: codecapture(compst, tree, tt, fl); break;
    case TRunTime: coderuntime(compst, tree, tt); break;
    case TGrammar: codegrammar(compst, tree); break;
    case TCall: codecall(compst, tree); break;
    case TSeq: {
      tt = codeseq1(compst, sib1(tree), sib2(tree), tt, fl);  /* code 'p1' */
      /* codegen(compst, p2, opt, tt, fl); */
      tree = sib2(tree); goto tailcall;
    }
    default: assert(0);
  }
}