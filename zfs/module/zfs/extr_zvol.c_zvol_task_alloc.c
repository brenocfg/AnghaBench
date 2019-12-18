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
struct TYPE_4__ {int /*<<< orphan*/  name2; int /*<<< orphan*/  name1; int /*<<< orphan*/  pool; int /*<<< orphan*/  value; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ zvol_task_t ;
typedef  int /*<<< orphan*/  zvol_async_op_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int MAXNAMELEN ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static zvol_task_t *
zvol_task_alloc(zvol_async_op_t op, const char *name1, const char *name2,
    uint64_t value)
{
	zvol_task_t *task;
	char *delim;

	/* Never allow tasks on hidden names. */
	if (name1[0] == '$')
		return (NULL);

	task = kmem_zalloc(sizeof (zvol_task_t), KM_SLEEP);
	task->op = op;
	task->value = value;
	delim = strchr(name1, '/');
	strlcpy(task->pool, name1, delim ? (delim - name1 + 1) : MAXNAMELEN);

	strlcpy(task->name1, name1, MAXNAMELEN);
	if (name2 != NULL)
		strlcpy(task->name2, name2, MAXNAMELEN);

	return (task);
}