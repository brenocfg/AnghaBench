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
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  attr_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_CONTEXT_CONTAINER ; 
 int /*<<< orphan*/  TYPE_CONTEXT_CONTAINER_NO_POINTERS ; 
 int write_type_tfs (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int write_embedded_types(FILE *file, const attr_list_t *attrs, type_t *type,
                                const char *name, int write_ptr, unsigned int *tfsoff)
{
    return write_type_tfs(file, 2, attrs, type, name, write_ptr ? TYPE_CONTEXT_CONTAINER : TYPE_CONTEXT_CONTAINER_NO_POINTERS, tfsoff);
}