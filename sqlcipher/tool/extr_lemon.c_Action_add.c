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
struct symbol {int dummy; } ;
struct state {int dummy; } ;
struct rule {int dummy; } ;
struct TYPE_2__ {struct rule* rp; struct state* stp; } ;
struct action {int type; TYPE_1__ x; scalar_t__ spOpt; struct symbol* sp; struct action* next; } ;
typedef  enum e_action { ____Placeholder_e_action } e_action ;

/* Variables and functions */
 struct action* Action_new () ; 
 int SHIFT ; 

void Action_add(
  struct action **app,
  enum e_action type,
  struct symbol *sp,
  char *arg
){
  struct action *newaction;
  newaction = Action_new();
  newaction->next = *app;
  *app = newaction;
  newaction->type = type;
  newaction->sp = sp;
  newaction->spOpt = 0;
  if( type==SHIFT ){
    newaction->x.stp = (struct state *)arg;
  }else{
    newaction->x.rp = (struct rule *)arg;
  }
}