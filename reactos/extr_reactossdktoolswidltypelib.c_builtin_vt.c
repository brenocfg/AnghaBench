#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
struct oatype {char const* kw; unsigned short vt; } ;

/* Variables and functions */
 unsigned int NTYPES ; 
 scalar_t__ TYPE_BASIC ; 
#define  TYPE_BASIC_CHAR 129 
#define  TYPE_BASIC_WCHAR 128 
 unsigned short VT_LPSTR ; 
 unsigned short VT_LPWSTR ; 
 scalar_t__ is_array (TYPE_1__ const*) ; 
 scalar_t__ is_string_type (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  kw_cmp_func (struct oatype*,struct oatype*) ; 
 struct oatype* oatypes ; 
 TYPE_1__* type_array_get_element (TYPE_1__ const*) ; 
 int type_basic_get_type (TYPE_1__ const*) ; 
 scalar_t__ type_get_type (TYPE_1__ const*) ; 
 TYPE_1__* type_pointer_get_ref (TYPE_1__ const*) ; 

__attribute__((used)) static unsigned short builtin_vt(const type_t *t)
{
  const char *kw = t->name;
  struct oatype key;
  const struct oatype *kwp;
  key.kw = kw;
#ifdef KW_BSEARCH
  kwp = bsearch(&key, oatypes, NTYPES, sizeof(oatypes[0]), kw_cmp_func);
#else
  {
    unsigned int i;
    for (kwp=NULL, i=0; i < NTYPES; i++)
      if (!kw_cmp_func(&key, &oatypes[i])) {
        kwp = &oatypes[i];
        break;
      }
  }
#endif
  if (kwp) {
    return kwp->vt;
  }
  if (is_string_type (t->attrs, t))
  {
    const type_t *elem_type;
    if (is_array(t))
      elem_type = type_array_get_element(t);
    else
      elem_type = type_pointer_get_ref(t);
    if (type_get_type(elem_type) == TYPE_BASIC)
    {
      switch (type_basic_get_type(elem_type))
      {
      case TYPE_BASIC_CHAR: return VT_LPSTR;
      case TYPE_BASIC_WCHAR: return VT_LPWSTR;
      default: break;
      }
    }
  }
  return 0;
}