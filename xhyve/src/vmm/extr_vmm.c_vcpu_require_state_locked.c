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
struct vcpu {int dummy; } ;
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int vcpu_set_state_locked (struct vcpu*,int,int) ; 
 int /*<<< orphan*/  xhyve_abort (char*,int,int) ; 

__attribute__((used)) static void
vcpu_require_state_locked(struct vcpu *vcpu, enum vcpu_state newstate)
{
	int error;

	if ((error = vcpu_set_state_locked(vcpu, newstate, false)) != 0)
		xhyve_abort("Error %d setting state to %d", error, newstate);
}