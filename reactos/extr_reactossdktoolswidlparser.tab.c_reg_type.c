#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* c_name; } ;
typedef  TYPE_1__ type_t ;
struct rtype {char const* name; int t; struct rtype* next; TYPE_1__* type; } ;
struct namespace {struct rtype** type_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  error_loc (char*) ; 
 int /*<<< orphan*/  fix_incomplete_types (TYPE_1__*) ; 
 char const* format_namespace (struct namespace*,char*,char*,char const*) ; 
 struct namespace global_namespace ; 
 int hash_ident (char const*) ; 
 scalar_t__ is_global_namespace (struct namespace*) ; 
 int tsSTRUCT ; 
 int tsUNION ; 
 struct rtype* xmalloc (int) ; 

type_t *reg_type(type_t *type, const char *name, struct namespace *namespace, int t)
{
  struct rtype *nt;
  int hash;
  if (!name) {
    error_loc("registering named type without name\n");
    return type;
  }
  if (!namespace)
    namespace = &global_namespace;
  hash = hash_ident(name);
  nt = xmalloc(sizeof(struct rtype));
  nt->name = name;
  if (is_global_namespace(namespace))
    type->c_name = name;
  else
    type->c_name = format_namespace(namespace, "__x_", "_C", name);
  nt->type = type;
  nt->t = t;
  nt->next = namespace->type_hash[hash];
  namespace->type_hash[hash] = nt;
  if ((t == tsSTRUCT || t == tsUNION))
    fix_incomplete_types(type);
  return type;
}