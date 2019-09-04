#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* name; int do_free; char const* mangled; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ type_info ;
typedef  TYPE_1__ exception ;
typedef  int /*<<< orphan*/  e3 ;
typedef  int /*<<< orphan*/  e2 ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  bAncientVersion ; 
 char* call_func1 (void*,TYPE_1__*) ; 
 TYPE_1__* call_func2 (void*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* p__RTtypeid (TYPE_1__*) ; 
 int /*<<< orphan*/  pexception_copy_ctor ; 
 int /*<<< orphan*/  pexception_ctor ; 
 void* pexception_default_ctor ; 
 void* pexception_dtor ; 
 int /*<<< orphan*/  pexception_opequals ; 
 void* pexception_scalar_dtor ; 
 void* pexception_vector_dtor ; 
 int /*<<< orphan*/ * pexception_vtable ; 
 void* pexception_what ; 
 int /*<<< orphan*/  poperator_delete ; 
 TYPE_1__* poperator_new (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void test_exception(void)
{
  static const char* e_name = "An exception name";
  char* name;
  exception e, e2, e3, *pe;

  if (!poperator_new || !poperator_delete ||
      !pexception_ctor || !pexception_copy_ctor || !pexception_default_ctor ||
      !pexception_dtor || !pexception_opequals || !pexception_what ||
      !pexception_vtable || !pexception_vector_dtor || !pexception_scalar_dtor)
    return;

  /* 'const char*&' ctor */
  memset(&e, 0, sizeof(e));
  call_func2(pexception_ctor, &e, &e_name);
  ok(e.vtable != NULL, "Null exception vtable for e\n");
  ok(e.name && e.name != e_name && !strcmp(e.name, "An exception name"), "Bad name '%s' for e\n", e.name);
  ok(e.do_free == 1, "do_free set to %d for e\n", e.do_free);

  /* Copy ctor */
  memset(&e2, 0, sizeof(e2));
  call_func2(pexception_copy_ctor, &e2, &e);
  ok(e2.vtable != NULL, "Null exception vtable for e2\n");
  ok(e2.name && e2.name != e.name && !strcmp(e2.name, "An exception name"), "Bad exception name for e2\n");
  ok(e2.do_free == 1, "do_free set to %d for e2\n", e2.do_free);

  /* Default ctor */
  memset(&e3, 1, sizeof(e3));
  call_func1(pexception_default_ctor, &e3);
  ok(e3.vtable != NULL, "Null exception vtable for e3\n");
  ok(e3.name == NULL, "Bad exception name for e3\n");
  ok(e3.do_free == 0, "do_free set to %d for e3\n", e3.do_free);

  ok(e.vtable == e2.vtable && e.vtable == e3.vtable, "exception vtables differ!\n");

  /* Test calling the dtors */
  call_func1(pexception_dtor, &e2);
  call_func1(pexception_dtor, &e3);

  /* Operator equals */
  memset(&e2, 0, sizeof(e2));
  call_func1(pexception_default_ctor, &e2);
  pe = call_func2(pexception_opequals, &e2, &e);
  ok(e2.vtable != NULL, "Null exception vtable for e2\n");
  ok(e2.name && e2.name != e.name && !strcmp(e2.name, "An exception name"), "Bad exception name for e2\n");
  ok(e2.do_free == 1, "do_free set to %d for e2\n", e2.do_free);
  ok(pe == &e2, "opequals didn't return e2\n");

  /* what() */
  name = call_func1(pexception_what, &e2);
  ok(e2.name == name, "Bad exception name from e2::what()\n");

  /* vtable ptr */
  ok(e2.vtable == pexception_vtable, "Bad vtable for e2\n");
  call_func1(pexception_dtor, &e2);

  /* new() */
  pe = poperator_new(sizeof(exception));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    call_func2(pexception_ctor, pe, &e_name);
    /* scalar dtor */
    call_func2(pexception_scalar_dtor, pe, 0); /* Shouldn't delete pe */
    pe->name = NULL;
    pe->do_free = 0;
    call_func2(pexception_scalar_dtor, pe, 1); /* Should delete pe */
  }

  pe = poperator_new(sizeof(exception));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    /* vector dtor, single element */
    call_func2(pexception_ctor, pe, &e_name);
    call_func2(pexception_vector_dtor, pe, 1); /* Should delete pe as single element*/
  }

  pe = poperator_new(sizeof(exception) * 4 + sizeof(size_t));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    /* vector dtor, multiple elements */
    char name[] = "a constant";
    *((size_t*)pe) = 3;
    pe = (exception*)((size_t*)pe + 1);
    call_func2(pexception_ctor, &pe[0], &e_name);
    call_func2(pexception_ctor, &pe[1], &e_name);
    call_func2(pexception_ctor, &pe[2], &e_name);
    pe[3].name = name;
    pe[3].do_free = 1; /* Crash if we try to free this */
    call_func2(pexception_vector_dtor, pe, 3); /* Should delete all 3 and then pe block */
  }

  /* test our exported vtable is kosher */
  pe = (void*)pexception_vtable; /* Use the exception struct to get vtable ptrs */
  pexception_vector_dtor = (void*)pe->vtable;
  pexception_what = (void*)pe->name;

  name = call_func1(pexception_what, &e);
  ok(e.name == name, "Bad exception name from vtable e::what()\n");

  if (p__RTtypeid && !bAncientVersion)
  {
    /* Check the rtti */
    type_info *ti = p__RTtypeid(&e);
    ok (ti && !strcmp(ti->mangled, ".?AVexception@@"), "bad rtti for e\n");

    if (ti)
    {
      /* Check the returned type_info has rtti too */
      type_info *ti2 = p__RTtypeid(ti);
      ok (ti2 != NULL && !strcmp(ti2->mangled, ".?AVtype_info@@"), "bad rtti for e's type_info\n");
    }
  }

  call_func2(pexception_vector_dtor, &e, 0); /* Should delete e.name, but not e */
}