#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ddirs; } ;
struct TYPE_3__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 size_t PEDIR_IMPORT ; 
 scalar_t__ cachesync ; 
 int get_le32 (void*) ; 
 scalar_t__ getprocaddressa ; 
 TYPE_2__ ih ; 
 scalar_t__ loadlibraryw ; 
 int print (char*,...) ; 
 int /*<<< orphan*/  set_le32 (void*,unsigned int) ; 
 scalar_t__ strcasecmp (void*,char*) ; 
 void* vaddr ; 

__attribute__((used)) static int import(void)
{
    if (ih.ddirs[PEDIR_IMPORT].vaddr == 0)
        return print("no imports?\n");
    print("loadlibraryw=%p,getprocaddressa=%p,cachesync=%p\n",
          loadlibraryw, getprocaddressa, cachesync);
    void *imports = vaddr + ih.ddirs[PEDIR_IMPORT].vaddr;
    while (get_le32(imports + 12))
    {
        if (strcasecmp(vaddr + get_le32(imports + 12), "coredll.dll") == 0)
        {
            void *coredll_imports = vaddr + get_le32(imports + 16);
            print("coredll_imports=%p\n", coredll_imports);
            void *oft =  vaddr + get_le32(imports);
            unsigned pos = 0;
            while (get_le32(oft + pos))
            {
                void *name = vaddr + get_le32(oft + pos) + 2;
                print("name=%s\n", (char*) name);
                if (strcasecmp(name, "loadlibraryw") == 0)
                    set_le32(coredll_imports + pos, (unsigned) loadlibraryw);
                else if (strcasecmp(name, "getprocaddressa") == 0)
                    set_le32(coredll_imports + pos, (unsigned) getprocaddressa);
                else if (strcasecmp(name, "cachesync") == 0)
                    set_le32(coredll_imports + pos, (unsigned) cachesync);
                pos += 4;
            }
            return 0;
        }
        imports += 20;
    }

    print("coredll.dll not found");
    return 1;
}