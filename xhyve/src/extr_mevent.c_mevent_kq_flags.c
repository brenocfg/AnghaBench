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
struct mevent {int me_state; } ;

/* Variables and functions */
 int EV_ADD ; 
 int EV_DELETE ; 
 int EV_DISABLE ; 
 int EV_ENABLE ; 
#define  MEV_ADD 131 
#define  MEV_DEL_PENDING 130 
#define  MEV_DISABLE 129 
#define  MEV_ENABLE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mevent_kq_flags(struct mevent *mevp)
{
	int ret;

	switch (mevp->me_state) {
	case MEV_ADD:
		ret = EV_ADD;		/* implicitly enabled */
		break;
	case MEV_ENABLE:
		ret = EV_ENABLE;
		break;
	case MEV_DISABLE:
		ret = EV_DISABLE;
		break;
	case MEV_DEL_PENDING:
		ret = EV_DELETE;
		break;
	default:
		assert(0);
		break;
	}

	return (ret);
}