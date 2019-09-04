#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; struct namespace* namespace; } ;
typedef  TYPE_1__ type_t ;
struct namespace {int dummy; } ;
typedef  enum type_type { ____Placeholder_type_type } type_type ;

/* Variables and functions */
 TYPE_1__* find_type (char*,struct namespace*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct namespace global_namespace ; 
 TYPE_1__* make_type (int) ; 
 TYPE_1__* reg_type (TYPE_1__*,char*,struct namespace*,int) ; 

type_t *get_type(enum type_type type, char *name, struct namespace *namespace, int t)
{
  type_t *tp;
  if (!namespace)
    namespace = &global_namespace;
  if (name) {
    tp = find_type(name, namespace, t);
    if (tp) {
      free(name);
      return tp;
    }
  }
  tp = make_type(type);
  tp->name = name;
  tp->namespace = namespace;
  if (!name) return tp;
  return reg_type(tp, name, namespace, t);
}