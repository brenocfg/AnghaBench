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
struct TYPE_2__ {int helpcontext; int version; int /*<<< orphan*/  uuid; int /*<<< orphan*/  libflags; int /*<<< orphan*/  lcid; int /*<<< orphan*/  syskind; int /*<<< orphan*/  helpfile; int /*<<< orphan*/  helpstring; int /*<<< orphan*/  name; } ;
struct sltg_typelib {int /*<<< orphan*/  index; TYPE_1__ library; } ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int add_index (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 short strlen (int /*<<< orphan*/ ) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static void *create_library_block(struct sltg_typelib *typelib, int *size, int *index)
{
    void *block;
    short *p;

    *size = sizeof(short) * 9 + sizeof(int) * 3 + sizeof(GUID);
    if (typelib->library.helpstring) *size += strlen(typelib->library.helpstring);
    if (typelib->library.helpfile) *size += strlen(typelib->library.helpfile);

    block = xmalloc(*size);
    p = block;
    *p++ = 0x51cc; /* magic */
    *p++ = 3; /* res02 */
    *p++ = typelib->library.name;
    *p++ = 0xffff; /* res06 */
    if (typelib->library.helpstring)
    {
        *p++ = strlen(typelib->library.helpstring);
        strcpy((char *)p, typelib->library.helpstring);
        p = (short *)((char *)p + strlen(typelib->library.helpstring));
    }
    else
        *p++ = 0xffff;
    if (typelib->library.helpfile)
    {
        *p++ = strlen(typelib->library.helpfile);
        strcpy((char *)p, typelib->library.helpfile);
        p = (short *)((char *)p + strlen(typelib->library.helpfile));
    }
    else
        *p++ = 0xffff;
    *(int *)p = typelib->library.helpcontext;
    p += 2;
    *p++ = typelib->library.syskind;
    *p++ = typelib->library.lcid;
    *(int *)p = 0; /* res12 */
    p += 2;
    *p++ = typelib->library.libflags;
    *(int *)p = typelib->library.version;
    p += 2;
    *(GUID *)p = typelib->library.uuid;

    *index = add_index(&typelib->index, "dir");

    return block;
}