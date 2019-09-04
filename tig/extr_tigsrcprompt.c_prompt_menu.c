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
struct menu_item {scalar_t__ hotkey; scalar_t__ text; } ;
struct TYPE_2__ {scalar_t__* bytes; } ;
struct key {TYPE_1__ data; } ;
typedef  enum input_status { ____Placeholder_input_status } input_status ;

/* Variables and functions */
 scalar_t__ COLS ; 
 int INPUT_CANCEL ; 
 int INPUT_OK ; 
 int INPUT_STOP ; 
#define  KEY_DOWN 134 
#define  KEY_ENTER 133 
#define  KEY_ESC 132 
#define  KEY_LEFT 131 
#define  KEY_RETURN 130 
#define  KEY_RIGHT 129 
#define  KEY_UP 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int get_input (scalar_t__,struct key*) ; 
 char key_to_control (struct key*) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  string_format (char*,char*,int,int) ; 
 int /*<<< orphan*/  update_status_with_context (char*,char*,char const*,scalar_t__,char const*) ; 

bool
prompt_menu(const char *prompt, const struct menu_item *items, int *selected)
{
	enum input_status status = INPUT_OK;
	char buf[128];
	struct key key;
	int size = 0;

	while (items[size].text)
		size++;

	assert(size > 0);

	curs_set(1);
	while (status == INPUT_OK) {
		const struct menu_item *item = &items[*selected];
		const char hotkey[] = { ' ', '[', (char) item->hotkey, ']', 0 };
		int i;

		if (!string_format(buf, "(%d of %d)", *selected + 1, size))
			buf[0] = 0;

		update_status_with_context(buf, "%s %s%s", prompt, item->text,
			      item->hotkey ? hotkey : "");

		switch (get_input(COLS - 1, &key)) {
		case KEY_RETURN:
		case KEY_ENTER:
		case '\n':
			status = INPUT_STOP;
			break;

		case KEY_LEFT:
		case KEY_UP:
			*selected = *selected - 1;
			if (*selected < 0)
				*selected = size - 1;
			break;

		case KEY_RIGHT:
		case KEY_DOWN:
			*selected = (*selected + 1) % size;
			break;

		case KEY_ESC:
			status = INPUT_CANCEL;
			break;

		default:
			if (key_to_control(&key) == 'C') {
				status = INPUT_CANCEL;
				break;
			}

			for (i = 0; items[i].text; i++)
				if (items[i].hotkey == key.data.bytes[0]) {
					*selected = i;
					status = INPUT_STOP;
					break;
				}
		}
	}
	curs_set(0);

	report_clear();

	return status != INPUT_CANCEL;
}