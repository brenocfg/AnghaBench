#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ type_t ;
struct sltg_typelib {int dummy; } ;
struct TYPE_6__ {int cval; } ;
typedef  TYPE_2__ expr_t ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ GUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_HELPCONTEXT ; 
 int /*<<< orphan*/  ATTR_UUID ; 
 int /*<<< orphan*/  add_name (struct sltg_typelib*,int /*<<< orphan*/ ) ; 
 void* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* new_index_name () ; 
 int /*<<< orphan*/  sltg_add_typeinfo (struct sltg_typelib*,void*,int,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 short strlen (char const*) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static const char *add_typeinfo_block(struct sltg_typelib *typelib, const type_t *type, int kind)
{
    const char *index_name, *other_name;
    void *block;
    short *p;
    int size, helpcontext = 0;
    GUID guid = { 0 };
    const expr_t *expr;

    index_name = new_index_name();
    other_name = new_index_name();

    expr = get_attrp(type->attrs, ATTR_HELPCONTEXT);
    if (expr) helpcontext = expr->cval;

    p = get_attrp(type->attrs, ATTR_UUID);
    if (p) guid = *(GUID *)p;

    size = sizeof(short) * 8 + 10 /* index_name */ * 2 + sizeof(int) + sizeof(GUID);

    block = xmalloc(size);
    p = block;
    *p++ = strlen(index_name);
    strcpy((char *)p, index_name);
    p = (short *)((char *)p + strlen(index_name));
    *p++ = strlen(other_name);
    strcpy((char *)p, other_name);
    p = (short *)((char *)p + strlen(other_name));
    *p++ = -1; /* res1a */
    *p++ = add_name(typelib, type->name); /* name offset */
    *p++ = 0; /* FIXME: helpstring */
    *p++ = -1; /* res20 */
    *(int *)p = helpcontext;
    p += 2;
    *p++ = -1; /* res26 */
    *(GUID *)p = guid;
    p += sizeof(GUID)/2;
    *p = kind;

    sltg_add_typeinfo(typelib, block, size, index_name);

    return index_name;
}