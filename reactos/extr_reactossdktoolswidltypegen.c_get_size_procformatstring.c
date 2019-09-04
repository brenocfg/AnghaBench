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
typedef  int /*<<< orphan*/  type_pred_t ;
typedef  int /*<<< orphan*/  statement_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  for_each_iface (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  get_size_procformatstring_iface ; 

unsigned int get_size_procformatstring(const statement_list_t *stmts, type_pred_t pred)
{
    unsigned int size = 1;
    for_each_iface(stmts, get_size_procformatstring_iface, pred, NULL, 0, &size);
    return size;
}