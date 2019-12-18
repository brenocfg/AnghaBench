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
struct sltg_typelib {int typeinfo_size; int /*<<< orphan*/  typeinfo_count; struct sltg_block* typeinfo; } ;
struct sltg_block {int length; struct sltg_block* next; scalar_t__ index_string; void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  chat (char*,void*,int,char const*) ; 
 struct sltg_block* xmalloc (int) ; 

__attribute__((used)) static void sltg_add_typeinfo(struct sltg_typelib *sltg, void *data, int size, const char *name)
{
    struct sltg_block *block = xmalloc(sizeof(*block));

    chat("sltg_add_typeinfo: %p,%d,%s\n", data, size, name);

    block->length = size;
    block->data = data;
    block->index_string = 0;
    block->next = NULL;

    if (sltg->typeinfo)
    {
        struct sltg_block *typeinfo = sltg->typeinfo;

        while (typeinfo->next)
            typeinfo = typeinfo->next;

        typeinfo->next = block;
    }
    else
        sltg->typeinfo = block;

    sltg->typeinfo_count++;
    sltg->typeinfo_size += size;
}