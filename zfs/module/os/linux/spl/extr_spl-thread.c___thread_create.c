#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tp_name_size; size_t tp_len; int tp_state; int /*<<< orphan*/ * tp_name; int /*<<< orphan*/  tp_pri; void* tp_args; int /*<<< orphan*/  tp_func; int /*<<< orphan*/  tp_magic; } ;
typedef  TYPE_1__ thread_priv_t ;
typedef  int /*<<< orphan*/  thread_func_t ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  pri_t ;
typedef  int /*<<< orphan*/  kthread_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  KM_PUSHPAGE ; 
 int /*<<< orphan*/  TP_MAGIC ; 
 void* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 struct task_struct* spl_kthread_create (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char const*,int) ; 
 char* strstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thread_generic_wrapper ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

kthread_t *
__thread_create(caddr_t stk, size_t  stksize, thread_func_t func,
    const char *name, void *args, size_t len, proc_t *pp, int state, pri_t pri)
{
	thread_priv_t *tp;
	struct task_struct *tsk;
	char *p;

	/* Option pp is simply ignored */
	/* Variable stack size unsupported */
	ASSERT(stk == NULL);

	tp = kmem_alloc(sizeof (thread_priv_t), KM_PUSHPAGE);
	if (tp == NULL)
		return (NULL);

	tp->tp_magic = TP_MAGIC;
	tp->tp_name_size = strlen(name) + 1;

	tp->tp_name = kmem_alloc(tp->tp_name_size, KM_PUSHPAGE);
	if (tp->tp_name == NULL) {
		kmem_free(tp, sizeof (thread_priv_t));
		return (NULL);
	}

	strncpy(tp->tp_name, name, tp->tp_name_size);

	/*
	 * Strip trailing "_thread" from passed name which will be the func
	 * name since the exposed API has no parameter for passing a name.
	 */
	p = strstr(tp->tp_name, "_thread");
	if (p)
		p[0] = '\0';

	tp->tp_func  = func;
	tp->tp_args  = args;
	tp->tp_len   = len;
	tp->tp_state = state;
	tp->tp_pri   = pri;

	tsk = spl_kthread_create(thread_generic_wrapper, (void *)tp,
	    "%s", tp->tp_name);
	if (IS_ERR(tsk))
		return (NULL);

	wake_up_process(tsk);
	return ((kthread_t *)tsk);
}