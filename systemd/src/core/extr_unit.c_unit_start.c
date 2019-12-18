#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  scalar_t__ UnitActiveState ;
struct TYPE_18__ {scalar_t__ load_state; int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  inactive_enter_timestamp; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_17__ {int (* start ) (TYPE_1__*) ;scalar_t__ once_only; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EALREADY ; 
 int EBADR ; 
 int /*<<< orphan*/  ECOMM ; 
 int EINVAL ; 
 int ENOLINK ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EPROTO ; 
 int ESTALE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ACTIVATING ; 
 scalar_t__ UNIT_IS_ACTIVE_OR_RELOADING (scalar_t__) ; 
 scalar_t__ UNIT_LOADED ; 
 scalar_t__ UNIT_MAINTENANCE ; 
 TYPE_15__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dual_timestamp_is_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_unit_debug_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int log_unit_notice_errno (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_1__*) ; 
 scalar_t__ unit_active_state (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_1__*) ; 
 TYPE_1__* unit_following (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_test_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_test_condition (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_type_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_verify_deps (TYPE_1__*) ; 

int unit_start(Unit *u) {
        UnitActiveState state;
        Unit *following;

        assert(u);

        /* If this is already started, then this will succeed. Note that this will even succeed if this unit
         * is not startable by the user. This is relied on to detect when we need to wait for units and when
         * waiting is finished. */
        state = unit_active_state(u);
        if (UNIT_IS_ACTIVE_OR_RELOADING(state))
                return -EALREADY;
        if (state == UNIT_MAINTENANCE)
                return -EAGAIN;

        /* Units that aren't loaded cannot be started */
        if (u->load_state != UNIT_LOADED)
                return -EINVAL;

        /* Refuse starting scope units more than once */
        if (UNIT_VTABLE(u)->once_only && dual_timestamp_is_set(&u->inactive_enter_timestamp))
                return -ESTALE;

        /* If the conditions failed, don't do anything at all. If we already are activating this call might
         * still be useful to speed up activation in case there is some hold-off time, but we don't want to
         * recheck the condition in that case. */
        if (state != UNIT_ACTIVATING &&
            !unit_test_condition(u))
                return log_unit_debug_errno(u, SYNTHETIC_ERRNO(ECOMM), "Starting requested but condition failed. Not starting unit.");

        /* If the asserts failed, fail the entire job */
        if (state != UNIT_ACTIVATING &&
            !unit_test_assert(u))
                return log_unit_notice_errno(u, SYNTHETIC_ERRNO(EPROTO), "Starting requested but asserts failed.");

        /* Units of types that aren't supported cannot be started. Note that we do this test only after the
         * condition checks, so that we rather return condition check errors (which are usually not
         * considered a true failure) than "not supported" errors (which are considered a failure).
         */
        if (!unit_type_supported(u->type))
                return -EOPNOTSUPP;

        /* Let's make sure that the deps really are in order before we start this. Normally the job engine
         * should have taken care of this already, but let's check this here again. After all, our
         * dependencies might not be in effect anymore, due to a reload or due to a failed condition. */
        if (!unit_verify_deps(u))
                return -ENOLINK;

        /* Forward to the main object, if we aren't it. */
        following = unit_following(u);
        if (following) {
                log_unit_debug(u, "Redirecting start request from %s to %s.", u->id, following->id);
                return unit_start(following);
        }

        /* If it is stopped, but we cannot start it, then fail */
        if (!UNIT_VTABLE(u)->start)
                return -EBADR;

        /* We don't suppress calls to ->start() here when we are already starting, to allow this request to
         * be used as a "hurry up" call, for example when the unit is in some "auto restart" state where it
         * waits for a holdoff timer to elapse before it will start again. */

        unit_add_to_dbus_queue(u);

        return UNIT_VTABLE(u)->start(u);
}