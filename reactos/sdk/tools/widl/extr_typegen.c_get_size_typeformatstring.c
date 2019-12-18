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
 int /*<<< orphan*/  FALSE ; 
 unsigned int process_tfs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_all_tfswrite (int /*<<< orphan*/ ) ; 

unsigned int get_size_typeformatstring(const statement_list_t *stmts, type_pred_t pred)
{
    set_all_tfswrite(FALSE);
    return process_tfs(NULL, stmts, pred);
}