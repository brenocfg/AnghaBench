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
struct re_object {int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  REOBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ME_CopyReObject (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REO_GETOBJ_ALL_INTERFACES ; 
 int /*<<< orphan*/  WARN (char*) ; 
 struct re_object* heap_alloc (int) ; 

__attribute__((used)) static struct re_object* create_re_object(const REOBJECT *reo)
{
  struct re_object *reobj = heap_alloc(sizeof(*reobj));

  if (!reobj)
  {
    WARN("Fail to allocate re_object.\n");
    return NULL;
  }
  ME_CopyReObject(&reobj->obj, reo, REO_GETOBJ_ALL_INTERFACES);
  return reobj;
}