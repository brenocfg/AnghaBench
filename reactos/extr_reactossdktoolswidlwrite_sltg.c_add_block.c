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
struct sltg_typelib {int /*<<< orphan*/  index; } ;
struct sltg_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_block_index (struct sltg_typelib*,void*,int,int) ; 
 int add_index (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  chat (char*,void*,int,char const*) ; 
 struct sltg_block* xmalloc (int) ; 

__attribute__((used)) static void add_block(struct sltg_typelib *sltg, void *data, int size, const char *name)
{
    struct sltg_block *block = xmalloc(sizeof(*block));
    int index;

    chat("add_block: %p,%d,\"%s\"\n", data, size, name);

    index = add_index(&sltg->index, name);

    add_block_index(sltg, data, size, index);
}