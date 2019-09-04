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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  for_each_iface (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  process_tfs_iface ; 

__attribute__((used)) static unsigned int process_tfs(FILE *file, const statement_list_t *stmts, type_pred_t pred)
{
    unsigned int typeformat_offset = 2;
    for_each_iface(stmts, process_tfs_iface, pred, file, 0, &typeformat_offset);
    return typeformat_offset + 1;
}