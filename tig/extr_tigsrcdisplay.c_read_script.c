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
struct key {int dummy; } ;
struct buffer {char* data; } ;
typedef  int /*<<< orphan*/  input_buffer ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int get_key_value (char const**,struct key*) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 int /*<<< orphan*/  io_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_get (int /*<<< orphan*/ *,struct buffer*,char,int) ; 
 int /*<<< orphan*/  memset (struct buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  script_io ; 
 size_t strspn (char*,char*) ; 

__attribute__((used)) static bool
read_script(struct key *key)
{
	static struct buffer input_buffer;
	static const char *line = "";
	enum status_code code;

	while (!line || !*line) {
		if (input_buffer.data && *input_buffer.data == ':') {
			line = "<Enter>";
			memset(&input_buffer, 0, sizeof(input_buffer));

		} else if (!io_get(&script_io, &input_buffer, '\n', true)) {
			io_done(&script_io);
			return false;
		} else if (input_buffer.data[strspn(input_buffer.data, " \t")] == '#') {
			continue;
		} else {
			line = input_buffer.data;
		}
	}

	code = get_key_value(&line, key);
	if (code != SUCCESS)
		die("Error reading script: %s", get_status_message(code));
	return true;
}