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
typedef  int /*<<< orphan*/  var_t ;
struct rconst {int /*<<< orphan*/ * var; struct rconst* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct rconst** const_hash ; 
 int /*<<< orphan*/  error_loc (char*,char const*) ; 
 size_t hash_ident (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

var_t *find_const(const char *name, int f)
{
  struct rconst *cur = const_hash[hash_ident(name)];
  while (cur && strcmp(cur->name, name))
    cur = cur->next;
  if (!cur) {
    if (f) error_loc("constant '%s' not found\n", name);
    return NULL;
  }
  return cur->var;
}