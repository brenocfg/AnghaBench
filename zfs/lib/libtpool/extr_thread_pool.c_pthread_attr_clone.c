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
struct sched_param {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int pthread_attr_getaffinity_np (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int pthread_attr_getdetachstate (int /*<<< orphan*/  const*,int*) ; 
 int pthread_attr_getguardsize (int /*<<< orphan*/  const*,size_t*) ; 
 int pthread_attr_getinheritsched (int /*<<< orphan*/  const*,int*) ; 
 int pthread_attr_getschedparam (int /*<<< orphan*/  const*,struct sched_param*) ; 
 int pthread_attr_getschedpolicy (int /*<<< orphan*/  const*,int*) ; 
 int pthread_attr_getscope (int /*<<< orphan*/  const*,int*) ; 
 int pthread_attr_getstack (int /*<<< orphan*/  const*,void**,size_t*) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int pthread_attr_setdetachstate (int /*<<< orphan*/ *,int) ; 
 int pthread_attr_setguardsize (int /*<<< orphan*/ *,size_t) ; 
 int pthread_attr_setinheritsched (int /*<<< orphan*/ *,int) ; 
 int pthread_attr_setschedparam (int /*<<< orphan*/ *,struct sched_param*) ; 
 int pthread_attr_setschedpolicy (int /*<<< orphan*/ *,int) ; 
 int pthread_attr_setscope (int /*<<< orphan*/ *,int) ; 
 int pthread_attr_setstack (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int
pthread_attr_clone(pthread_attr_t *attr, const pthread_attr_t *old_attr)
{
	int error;

	error = pthread_attr_init(attr);
	if (error || (old_attr == NULL))
		return (error);

#ifdef __GLIBC__
	cpu_set_t cpuset;
	size_t cpusetsize = sizeof (cpuset);
	error = pthread_attr_getaffinity_np(old_attr, cpusetsize, &cpuset);
	if (error == 0)
		error = pthread_attr_setaffinity_np(attr, cpusetsize, &cpuset);
	if (error)
		goto error;
#endif /* __GLIBC__ */

	int detachstate;
	error = pthread_attr_getdetachstate(old_attr, &detachstate);
	if (error == 0)
		error = pthread_attr_setdetachstate(attr, detachstate);
	if (error)
		goto error;

	size_t guardsize;
	error = pthread_attr_getguardsize(old_attr, &guardsize);
	if (error == 0)
		error = pthread_attr_setguardsize(attr, guardsize);
	if (error)
		goto error;

	int inheritsched;
	error = pthread_attr_getinheritsched(old_attr, &inheritsched);
	if (error == 0)
		error = pthread_attr_setinheritsched(attr, inheritsched);
	if (error)
		goto error;

	struct sched_param param;
	error = pthread_attr_getschedparam(old_attr, &param);
	if (error == 0)
		error = pthread_attr_setschedparam(attr, &param);
	if (error)
		goto error;

	int policy;
	error = pthread_attr_getschedpolicy(old_attr, &policy);
	if (error == 0)
		error = pthread_attr_setschedpolicy(attr, policy);
	if (error)
		goto error;

	int scope;
	error = pthread_attr_getscope(old_attr, &scope);
	if (error == 0)
		error = pthread_attr_setscope(attr, scope);
	if (error)
		goto error;

	void *stackaddr;
	size_t stacksize;
	error = pthread_attr_getstack(old_attr, &stackaddr, &stacksize);
	if (error == 0)
		error = pthread_attr_setstack(attr, stackaddr, stacksize);
	if (error)
		goto error;

	return (0);
error:
	pthread_attr_destroy(attr);
	return (error);
}