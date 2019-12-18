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

/* Variables and functions */
 int /*<<< orphan*/  AutomountState ; 
 int /*<<< orphan*/  DUMP_STRING_TABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeviceState ; 
 int /*<<< orphan*/  MountState ; 
 int /*<<< orphan*/  PathState ; 
 int /*<<< orphan*/  ScopeState ; 
 int /*<<< orphan*/  ServiceState ; 
 int /*<<< orphan*/  SliceState ; 
 int /*<<< orphan*/  SocketState ; 
 int /*<<< orphan*/  SwapState ; 
 int /*<<< orphan*/  TargetState ; 
 int /*<<< orphan*/  TimerState ; 
 int /*<<< orphan*/  UnitActiveState ; 
 int /*<<< orphan*/  UnitFileState ; 
 int /*<<< orphan*/  UnitLoadState ; 
 int /*<<< orphan*/  _AUTOMOUNT_STATE_MAX ; 
 int /*<<< orphan*/  _DEVICE_STATE_MAX ; 
 int /*<<< orphan*/  _MOUNT_STATE_MAX ; 
 int /*<<< orphan*/  _PATH_STATE_MAX ; 
 int /*<<< orphan*/  _SCOPE_STATE_MAX ; 
 int /*<<< orphan*/  _SERVICE_STATE_MAX ; 
 int /*<<< orphan*/  _SLICE_STATE_MAX ; 
 int /*<<< orphan*/  _SOCKET_STATE_MAX ; 
 int /*<<< orphan*/  _SWAP_STATE_MAX ; 
 int /*<<< orphan*/  _TARGET_STATE_MAX ; 
 int /*<<< orphan*/  _TIMER_STATE_MAX ; 
 int /*<<< orphan*/  _UNIT_ACTIVE_STATE_MAX ; 
 int /*<<< orphan*/  _UNIT_FILE_STATE_MAX ; 
 int /*<<< orphan*/  _UNIT_LOAD_STATE_MAX ; 
 int /*<<< orphan*/  arg_no_legend ; 
 int /*<<< orphan*/  automount_state ; 
 int /*<<< orphan*/  device_state ; 
 int /*<<< orphan*/  mount_state ; 
 int /*<<< orphan*/  path_state ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  scope_state ; 
 int /*<<< orphan*/  service_state ; 
 int /*<<< orphan*/  slice_state ; 
 int /*<<< orphan*/  socket_state ; 
 int /*<<< orphan*/  swap_state ; 
 int /*<<< orphan*/  target_state ; 
 int /*<<< orphan*/  timer_state ; 
 int /*<<< orphan*/  unit_active_state ; 
 int /*<<< orphan*/  unit_file_state ; 
 int /*<<< orphan*/  unit_load_state ; 

__attribute__((used)) static void help_states(void) {
        if (!arg_no_legend)
                puts("Available unit load states:");
        DUMP_STRING_TABLE(unit_load_state, UnitLoadState, _UNIT_LOAD_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable unit active states:");
        DUMP_STRING_TABLE(unit_active_state, UnitActiveState, _UNIT_ACTIVE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable unit file states:");
        DUMP_STRING_TABLE(unit_file_state, UnitFileState, _UNIT_FILE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable automount unit substates:");
        DUMP_STRING_TABLE(automount_state, AutomountState, _AUTOMOUNT_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable device unit substates:");
        DUMP_STRING_TABLE(device_state, DeviceState, _DEVICE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable mount unit substates:");
        DUMP_STRING_TABLE(mount_state, MountState, _MOUNT_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable path unit substates:");
        DUMP_STRING_TABLE(path_state, PathState, _PATH_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable scope unit substates:");
        DUMP_STRING_TABLE(scope_state, ScopeState, _SCOPE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable service unit substates:");
        DUMP_STRING_TABLE(service_state, ServiceState, _SERVICE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable slice unit substates:");
        DUMP_STRING_TABLE(slice_state, SliceState, _SLICE_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable socket unit substates:");
        DUMP_STRING_TABLE(socket_state, SocketState, _SOCKET_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable swap unit substates:");
        DUMP_STRING_TABLE(swap_state, SwapState, _SWAP_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable target unit substates:");
        DUMP_STRING_TABLE(target_state, TargetState, _TARGET_STATE_MAX);

        if (!arg_no_legend)
                puts("\nAvailable timer unit substates:");
        DUMP_STRING_TABLE(timer_state, TimerState, _TIMER_STATE_MAX);
}