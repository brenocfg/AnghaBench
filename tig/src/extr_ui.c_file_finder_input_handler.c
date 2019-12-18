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
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;
struct key {TYPE_1__ data; } ;
struct input {struct file_finder* data; } ;
struct file_finder {size_t searchlen; int /*<<< orphan*/ ** search; int /*<<< orphan*/  keymap; } ;
typedef  enum input_status { ____Placeholder_input_status } input_status ;

/* Variables and functions */
 int INPUT_CANCEL ; 
 int INPUT_DELETE ; 
 int INPUT_OK ; 
 int INPUT_SKIP ; 
#define  REQ_BACK 133 
#define  REQ_FIND_NEXT 132 
#define  REQ_FIND_PREV 131 
#define  REQ_PARENT 130 
#define  REQ_VIEW_CLOSE 129 
#define  REQ_VIEW_CLOSE_NO_QUIT 128 
 int /*<<< orphan*/  argv_append (int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_finder_draw (struct file_finder*) ; 
 int /*<<< orphan*/  file_finder_move (struct file_finder*,int) ; 
 int /*<<< orphan*/  file_finder_update (struct file_finder*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int get_keybinding (int /*<<< orphan*/ ,struct key*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_to_value (struct key*) ; 
 int prompt_default_handler (struct input*,struct key*) ; 

__attribute__((used)) static enum input_status
file_finder_input_handler(struct input *input, struct key *key)
{
	struct file_finder *finder = input->data;
	enum input_status status;

	status = prompt_default_handler(input, key);
	if (status == INPUT_DELETE) {
		if (finder->searchlen > 0) {
			finder->searchlen--;
			free((void *) finder->search[finder->searchlen]);
			finder->search[finder->searchlen] = NULL;
		}
		file_finder_update(finder);
		file_finder_move(finder, 0);
		file_finder_draw(finder);
		return status;
	}

	if (status != INPUT_SKIP)
		return status;

	switch (get_keybinding(finder->keymap, key, 1, NULL)) {
	case REQ_FIND_PREV:
		file_finder_move(finder, -1);
		file_finder_draw(finder);
		return INPUT_SKIP;

	case REQ_FIND_NEXT:
		file_finder_move(finder, +1);
		file_finder_draw(finder);
		return INPUT_SKIP;

	case REQ_BACK:
	case REQ_PARENT:
	case REQ_VIEW_CLOSE:
	case REQ_VIEW_CLOSE_NO_QUIT:
		return INPUT_CANCEL;

	default:
		if (key_to_value(key) == 0) {
			argv_append(&finder->search, key->data.bytes);
			finder->searchlen++;
			file_finder_update(finder);
			file_finder_move(finder, 0);
			file_finder_draw(finder);
			return INPUT_OK;
		}

		/* Catch all non-multibyte keys. */
		return INPUT_SKIP;
	}
}