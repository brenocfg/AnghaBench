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
struct symbol {int prec; scalar_t__ useCnt; int /*<<< orphan*/  name; scalar_t__ datatype; scalar_t__ destLineno; scalar_t__ destructor; int /*<<< orphan*/  lambda; scalar_t__ firstset; int /*<<< orphan*/  assoc; scalar_t__ fallback; scalar_t__ rule; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ ISUPPER (char const) ; 
 int /*<<< orphan*/  LEMON_FALSE ; 
 int /*<<< orphan*/  MemoryCheck (struct symbol*) ; 
 int /*<<< orphan*/  NONTERMINAL ; 
 int /*<<< orphan*/  Strsafe (char const*) ; 
 struct symbol* Symbol_find (char const*) ; 
 int /*<<< orphan*/  Symbol_insert (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TERMINAL ; 
 int /*<<< orphan*/  UNK ; 
 scalar_t__ calloc (int,int) ; 

struct symbol *Symbol_new(const char *x)
{
  struct symbol *sp;

  sp = Symbol_find(x);
  if( sp==0 ){
    sp = (struct symbol *)calloc(1, sizeof(struct symbol) );
    MemoryCheck(sp);
    sp->name = Strsafe(x);
    sp->type = ISUPPER(*x) ? TERMINAL : NONTERMINAL;
    sp->rule = 0;
    sp->fallback = 0;
    sp->prec = -1;
    sp->assoc = UNK;
    sp->firstset = 0;
    sp->lambda = LEMON_FALSE;
    sp->destructor = 0;
    sp->destLineno = 0;
    sp->datatype = 0;
    sp->useCnt = 0;
    Symbol_insert(sp,sp->name);
  }
  sp->useCnt++;
  return sp;
}