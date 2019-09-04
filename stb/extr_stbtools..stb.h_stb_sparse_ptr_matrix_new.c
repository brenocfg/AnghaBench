#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int val_size; int /*<<< orphan*/  arena; } ;
typedef  TYPE_1__ stb_spmatrix ;

/* Variables and functions */
 TYPE_1__* stb__spmatrix_create () ; 
 int /*<<< orphan*/  stb_malloc_global (int) ; 

stb_spmatrix *stb_sparse_ptr_matrix_new(int val_size)
{
   stb_spmatrix *m = stb__spmatrix_create();
   if (m) m->val_size = val_size;
   if (m) m->arena = stb_malloc_global(1);
   return m;
}