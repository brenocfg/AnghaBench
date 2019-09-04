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
struct vcpu {int state; int /*<<< orphan*/  state_sleep_cnd; int /*<<< orphan*/  state_sleep_mtx; } ;
struct timespec {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  VCPU_FROZEN 131 
#define  VCPU_IDLE 130 
#define  VCPU_RUNNING 129 
#define  VCPU_SLEEPING 128 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_timedwait_relative_np (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 

__attribute__((used)) static int
vcpu_set_state_locked(struct vcpu *vcpu, enum vcpu_state newstate,
    bool from_idle)
{
	int error;
	const struct timespec ts = {.tv_sec = 1, .tv_nsec = 0}; /* 1 second */

	/*
	 * State transitions from the vmmdev_ioctl() must always begin from
	 * the VCPU_IDLE state. This guarantees that there is only a single
	 * ioctl() operating on a vcpu at any point.
	 */
	if (from_idle) {
		while (vcpu->state != VCPU_IDLE) {
			pthread_mutex_lock(&vcpu->state_sleep_mtx);
			vcpu_unlock(vcpu);
			pthread_cond_timedwait_relative_np(&vcpu->state_sleep_cnd,
				&vcpu->state_sleep_mtx, &ts);
			vcpu_lock(vcpu);
			pthread_mutex_unlock(&vcpu->state_sleep_mtx);
			//msleep_spin(&vcpu->state, &vcpu->mtx, "vmstat", hz);
		}
	} else {
		KASSERT(vcpu->state != VCPU_IDLE, ("invalid transition from "
		    "vcpu idle state"));
	}

	/*
	 * The following state transitions are allowed:
	 * IDLE -> FROZEN -> IDLE
	 * FROZEN -> RUNNING -> FROZEN
	 * FROZEN -> SLEEPING -> FROZEN
	 */
	switch (vcpu->state) {
	case VCPU_IDLE:
	case VCPU_RUNNING:
	case VCPU_SLEEPING:
		error = (newstate != VCPU_FROZEN);
		break;
	case VCPU_FROZEN:
		error = (newstate == VCPU_FROZEN);
		break;
	}

	if (error)
		return (EBUSY);

	vcpu->state = newstate;

	if (newstate == VCPU_IDLE)
		pthread_cond_broadcast(&vcpu->state_sleep_cnd);
		//wakeup(&vcpu->state);

	return (0);
}