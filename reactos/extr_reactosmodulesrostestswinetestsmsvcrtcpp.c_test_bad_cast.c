#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* mangled; } ;
typedef  TYPE_1__ type_info ;
struct TYPE_11__ {char const* name; int do_free; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_2__ exception ;
typedef  int /*<<< orphan*/  e3 ;
typedef  int /*<<< orphan*/  e2 ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  bAncientVersion ; 
 char* call_func1 (void*,TYPE_2__*) ; 
 TYPE_2__* call_func2 (void*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 TYPE_1__* p__RTtypeid (TYPE_2__*) ; 
 int /*<<< orphan*/  pbad_cast_copy_ctor ; 
 int /*<<< orphan*/  pbad_cast_ctor ; 
 scalar_t__ pbad_cast_ctor2 ; 
 void* pbad_cast_ctor_closure ; 
 void* pbad_cast_dtor ; 
 int /*<<< orphan*/  pbad_cast_opequals ; 
 void* pbad_cast_scalar_dtor ; 
 void* pbad_cast_vector_dtor ; 
 scalar_t__ pbad_cast_vtable ; 
 void* pbad_cast_what ; 
 void* pexception_default_ctor ; 
 int /*<<< orphan*/ * pexception_vtable ; 
 int /*<<< orphan*/  poperator_delete ; 
 TYPE_2__* poperator_new (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void test_bad_cast(void)
{
  static const char* e_name = "A bad_cast name";
  char* name;
  exception e, e2, e3, *pe;

  if (!poperator_new || !poperator_delete ||
      !pbad_cast_ctor || !pbad_cast_copy_ctor ||
      !pbad_cast_dtor || !pbad_cast_opequals || !pbad_cast_what ||
      !pbad_cast_vtable || !pbad_cast_vector_dtor || !pbad_cast_scalar_dtor)
    return;

  if (pbad_cast_ctor2)
  {
    /* 'const char*' ctor */
    memset(&e, 0, sizeof(e));
    call_func2(pbad_cast_ctor2, &e, e_name);
    ok(e.vtable != NULL, "Null bad_cast vtable for e\n");
    ok(e.name && e.name != e_name && !strcmp(e.name, "A bad_cast name"), "Bad name '%s' for e\n", e.name);
    ok(e.do_free == 1, "do_free set to %d for e\n", e.do_free);
    call_func1(pbad_cast_dtor, &e);
  }

  /* 'const char*&' ctor */
  memset(&e, 0, sizeof(e));
  call_func2(pbad_cast_ctor, &e, &e_name);
  ok(e.vtable != NULL, "Null bad_cast vtable for e\n");
  ok(e.name && e.name != e_name && !strcmp(e.name, "A bad_cast name"), "Bad name '%s' for e\n", e.name);
  ok(e.do_free == 1, "do_free set to %d for e\n", e.do_free);

  /* Copy ctor */
  memset(&e2, 0, sizeof(e2));
  call_func2(pbad_cast_copy_ctor, &e2, &e);
  ok(e2.vtable != NULL, "Null bad_cast vtable for e2\n");
  ok(e2.name && e2.name != e.name && !strcmp(e2.name, "A bad_cast name"), "Bad name '%s' for e2\n", e2.name);
  ok(e2.do_free == 1, "do_free set to %d for e2\n", e2.do_free);

  /* Ctor closure */
  if (pbad_cast_ctor_closure)
  {
    memset(&e3, 1, sizeof(e3));
    call_func1(pbad_cast_ctor_closure, &e3);
    ok(e3.vtable != NULL, "Null bad_cast vtable for e3\n");
    ok(e3.name && !strcmp(e3.name, "bad cast"), "Bad bad_cast name for e3\n");
    ok(e3.do_free == 1, "do_free set to %d for e3\n", e3.do_free);
    ok(e.vtable == e3.vtable, "bad_cast closure vtables differ!\n");
    call_func1(pbad_cast_dtor, &e3);
  }
  ok(e.vtable == e2.vtable, "bad_cast vtables differ!\n");

  /* Test calling the dtors */
  call_func1(pbad_cast_dtor, &e2);

  /* Operator equals */
  memset(&e2, 1, sizeof(e2));
  call_func1(pexception_default_ctor, &e2);
  pe = call_func2(pbad_cast_opequals, &e2, &e);
  ok(e2.vtable != NULL, "Null bad_cast vtable for e2\n");
  ok(e2.name && e2.name != e.name && !strcmp(e2.name, "A bad_cast name"), "Bad bad_cast name for e2\n");
  ok(e2.do_free == 1, "do_free set to %d for e2\n", e2.do_free);
  ok(pe == &e2, "opequals didn't return e2\n");

  /* what() */
  name = call_func1(pbad_cast_what, &e2);
  ok(e2.name == name, "Bad bad_cast name from e2::what()\n");

  /* vtable ptr */
  ok(e2.vtable == pexception_vtable, "Bad vtable for e2\n");
  call_func1(pbad_cast_dtor, &e2);

  /* new() */
  pe = poperator_new(sizeof(exception));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    call_func2(pbad_cast_ctor, pe, &e_name);
    /* scalar dtor */
    call_func2(pbad_cast_scalar_dtor, pe, 0); /* Shouldn't delete pe */
    pe->name = NULL;
    pe->do_free = 0;
    call_func2(pbad_cast_scalar_dtor, pe, 1); /* Should delete pe */
  }

  pe = poperator_new(sizeof(exception));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    /* vector dtor, single element */
    call_func2(pbad_cast_ctor, pe, &e_name);
    call_func2(pbad_cast_vector_dtor, pe, 1); /* Should delete pe as single element*/
  }

  pe = poperator_new(sizeof(exception) * 4 + sizeof(size_t));
  ok(pe != NULL, "new() failed\n");
  if (pe)
  {
    /* vector dtor, multiple elements */
    *((size_t*)pe) = 3;
    pe = (exception*)((size_t*)pe + 1);
    call_func2(pbad_cast_ctor, &pe[0], &e_name);
    call_func2(pbad_cast_ctor, &pe[1], &e_name);
    call_func2(pbad_cast_ctor, &pe[2], &e_name);
    pe[3].name = 0;
    pe[3].do_free = 1; /* Crash if we try to free this element */
    call_func2(pbad_cast_vector_dtor, pe, 3); /* Should delete all 3 and then pe block */
  }

  /* test our exported vtable is kosher */
  pe = (void*)pbad_cast_vtable; /* Use the exception struct to get vtable ptrs */
  pbad_cast_vector_dtor = (void*)pe->vtable;
  pbad_cast_what = (void*)pe->name;

  name = call_func1(pbad_cast_what, &e);
  ok(e.name == name, "Bad bad_cast name from vtable e::what()\n");

  if (p__RTtypeid && !bAncientVersion)
  {
    /* Check the rtti */
    type_info *ti = p__RTtypeid(&e);
    ok (ti != NULL && !strcmp(ti->mangled, ".?AVbad_cast@@"), "bad rtti for e\n");
  }
  call_func2(pbad_cast_vector_dtor, &e, 0); /* Should delete e.name, but not e */
}