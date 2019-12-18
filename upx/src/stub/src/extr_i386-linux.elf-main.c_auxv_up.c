#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int a_val; } ;
struct TYPE_8__ {TYPE_1__ a_un; } ;
typedef  TYPE_2__ Elf32_auxv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,TYPE_2__*,unsigned int const,unsigned int const) ; 
 TYPE_2__* auxv_find (TYPE_2__*,unsigned int const) ; 

__attribute__((used)) static void
#if defined(__i386__)  /*{*/
__attribute__((regparm(3), stdcall))
#endif  /*}*/
auxv_up(Elf32_auxv_t *av, unsigned const type, unsigned const value)
{
    DPRINTF("auxv_up  %%p %%x %%x\\n",av,type,value);
    av = auxv_find(av, type);
    if (av) {
        av->a_un.a_val = value;
    }
}