#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct swaynag_button {scalar_t__ type; int /*<<< orphan*/  action; scalar_t__ terminal; int /*<<< orphan*/  text; } ;
struct TYPE_2__ {int visible; } ;
struct swaynag {int run_display; TYPE_1__ details; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ SWAYNAG_ACTION_DISMISS ; 
 scalar_t__ SWAYNAG_ACTION_EXPAND ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  render_frame (struct swaynag*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  swaynag_destroy (struct swaynag*) ; 
 int /*<<< orphan*/  terminal_execute (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swaynag_button_execute(struct swaynag *swaynag,
		struct swaynag_button *button) {
	sway_log(SWAY_DEBUG, "Executing [%s]: %s", button->text, button->action);
	if (button->type == SWAYNAG_ACTION_DISMISS) {
		swaynag->run_display = false;
	} else if (button->type == SWAYNAG_ACTION_EXPAND) {
		swaynag->details.visible = !swaynag->details.visible;
		render_frame(swaynag);
	} else {
		pid_t pid = fork();
		if (pid < 0) {
			sway_log_errno(SWAY_DEBUG, "Failed to fork");
			return;
		} else if (pid == 0) {
			// Child process. Will be used to prevent zombie processes
			pid = fork();
			if (pid < 0) {
				sway_log_errno(SWAY_DEBUG, "Failed to fork");
				return;
			} else if (pid == 0) {
				// Child of the child. Will be reparented to the init process
				char *terminal = getenv("TERMINAL");
				if (button->terminal && terminal && strlen(terminal)) {
					sway_log(SWAY_DEBUG, "Found $TERMINAL: %s", terminal);
					if (!terminal_execute(terminal, button->action)) {
						swaynag_destroy(swaynag);
						_exit(EXIT_FAILURE);
					}
				} else {
					if (button->terminal) {
						sway_log(SWAY_DEBUG,
								"$TERMINAL not found. Running directly");
					}
					execl("/bin/sh", "/bin/sh", "-c", button->action, NULL);
					sway_log_errno(SWAY_DEBUG, "execl failed");
					_exit(EXIT_FAILURE);
				}
			}
			_exit(EXIT_SUCCESS);
		}
		if (waitpid(pid, NULL, 0) < 0) {
			sway_log_errno(SWAY_DEBUG, "waitpid failed");
		}
	}
}