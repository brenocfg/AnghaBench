#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ var_t ;
struct rconst {struct rconst* next; TYPE_1__* var; scalar_t__ name; } ;

/* Variables and functions */
 struct rconst** const_hash ; 
 int /*<<< orphan*/  error_loc (char*) ; 
 int hash_ident (scalar_t__) ; 
 struct rconst* xmalloc (int) ; 

__attribute__((used)) static var_t *reg_const(var_t *var)
{
  struct rconst *nc;
  int hash;
  if (!var->name) {
    error_loc("registering constant without name\n");
    return var;
  }
  hash = hash_ident(var->name);
  nc = xmalloc(sizeof(struct rconst));
  nc->name = var->name;
  nc->var = var;
  nc->next = const_hash[hash];
  const_hash[hash] = nc;
  return var;
}