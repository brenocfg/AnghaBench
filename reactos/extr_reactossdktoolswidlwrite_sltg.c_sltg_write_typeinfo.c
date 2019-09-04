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
struct sltg_typelib {short typeinfo_count; struct sltg_block* typeinfo; } ;
struct sltg_block {int length; short* data; struct sltg_block* next; } ;
typedef  int /*<<< orphan*/  count ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chat (char*,int,int) ; 
 int /*<<< orphan*/  put_data (short*,int) ; 

__attribute__((used)) static void sltg_write_typeinfo(struct sltg_typelib *typelib)
{
    int i;
    struct sltg_block *block;
    short count = typelib->typeinfo_count;

    put_data(&count, sizeof(count));

    block = typelib->typeinfo;
    for (i = 0; i < typelib->typeinfo_count; i++)
    {
        chat("sltg_write_typeinfo: writing block %d: %d bytes\n", i, block->length);

        put_data(block->data, block->length);
        block = block->next;
    }
    assert(block == NULL);
}