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
struct status_line {int protocol; size_t buffer_size; char* buffer; int click_events; int stop_signal; int cont_signal; char* text; int /*<<< orphan*/  read; int /*<<< orphan*/  buffer_index; int /*<<< orphan*/  tokener; int /*<<< orphan*/  blocks; int /*<<< orphan*/  write_fd; int /*<<< orphan*/  read_fd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  FIONREAD ; 
#define  PROTOCOL_I3BAR 130 
#define  PROTOCOL_TEXT 129 
#define  PROTOCOL_UNDEF 128 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int getline (char**,int*,int /*<<< orphan*/ ) ; 
 int i3bar_handle_readable (struct status_line*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  json_object_get_boolean (int /*<<< orphan*/ *) ; 
 int json_object_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_tokener_new () ; 
 int /*<<< orphan*/ * json_tokener_parse (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  status_error (struct status_line*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

bool status_handle_readable(struct status_line *status) {
	ssize_t read_bytes = 1;
	switch (status->protocol) {
	case PROTOCOL_UNDEF:
		errno = 0;
		int available_bytes;
		if (ioctl(status->read_fd, FIONREAD, &available_bytes) == -1) {
			sway_log(SWAY_ERROR, "Unable to read status command output size");
			status_error(status, "[error reading from status command]");
			return true;
		}

		if ((size_t)available_bytes + 1 > status->buffer_size) {
			// need room for leading '\0' too
			status->buffer_size = available_bytes + 1;
			status->buffer = realloc(status->buffer, status->buffer_size);
		}
		if (status->buffer == NULL) {
			sway_log_errno(SWAY_ERROR, "Unable to read status line");
			status_error(status, "[error reading from status command]");
			return true;
		}

		read_bytes = read(status->read_fd, status->buffer, available_bytes);
		if (read_bytes != available_bytes) {
			status_error(status, "[error reading from status command]");
			return true;
		}
		status->buffer[available_bytes] = 0;

		// the header must be sent completely the first time round
		char *newline = strchr(status->buffer, '\n');
		json_object *header, *version;
		if (newline != NULL
				&& (header = json_tokener_parse(status->buffer))
				&& json_object_object_get_ex(header, "version", &version)
				&& json_object_get_int(version) == 1) {
			sway_log(SWAY_DEBUG, "Using i3bar protocol.");
			status->protocol = PROTOCOL_I3BAR;

			json_object *click_events;
			if (json_object_object_get_ex(header, "click_events", &click_events)
					&& json_object_get_boolean(click_events)) {
				sway_log(SWAY_DEBUG, "Enabling click events.");
				status->click_events = true;
				if (write(status->write_fd, "[\n", 2) != 2) {
					status_error(status, "[failed to write to status command]");
					json_object_put(header);
					return true;
				}
			}

			json_object *signal;
			if (json_object_object_get_ex(header, "stop_signal", &signal)) {
				status->stop_signal = json_object_get_int(signal);
				sway_log(SWAY_DEBUG, "Setting stop signal to %d", status->stop_signal);
			}
			if (json_object_object_get_ex(header, "cont_signal", &signal)) {
				status->cont_signal = json_object_get_int(signal);
				sway_log(SWAY_DEBUG, "Setting cont signal to %d", status->cont_signal);
			}

			json_object_put(header);

			wl_list_init(&status->blocks);
			status->tokener = json_tokener_new();
			status->buffer_index = strlen(newline + 1);
			memmove(status->buffer, newline + 1, status->buffer_index + 1);
			return i3bar_handle_readable(status);
		}

		sway_log(SWAY_DEBUG, "Using text protocol.");
		status->protocol = PROTOCOL_TEXT;
		status->text = status->buffer;
		// intentional fall-through
	case PROTOCOL_TEXT:
		errno = 0;
		while (true) {
			if (status->buffer[read_bytes - 1] == '\n') {
				status->buffer[read_bytes - 1] = '\0';
			}
			read_bytes = getline(&status->buffer,
					&status->buffer_size, status->read);
			if (errno == EAGAIN) {
				clearerr(status->read);
				return true;
			} else if (errno) {
				status_error(status, "[error reading from status command]");
				return true;
			}
		}
	case PROTOCOL_I3BAR:
		return i3bar_handle_readable(status);
	default:
		return false;
	}
}