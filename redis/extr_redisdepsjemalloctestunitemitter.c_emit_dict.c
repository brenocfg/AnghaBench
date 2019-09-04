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
typedef  int /*<<< orphan*/  emitter_t ;

/* Variables and functions */
 int /*<<< orphan*/  emitter_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_dict_begin (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  emitter_dict_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_kv (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_kv_note (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  emitter_type_bool ; 
 int /*<<< orphan*/  emitter_type_int ; 
 int /*<<< orphan*/  emitter_type_string ; 

__attribute__((used)) static void
emit_dict(emitter_t *emitter) {
	bool b_false = false;
	bool b_true = true;
	int i_123 = 123;
	const char *str = "a string";

	emitter_begin(emitter);
	emitter_dict_begin(emitter, "foo", "This is the foo table:");
	emitter_kv(emitter, "abc", "ABC", emitter_type_bool, &b_false);
	emitter_kv(emitter, "def", "DEF", emitter_type_bool, &b_true);
	emitter_kv_note(emitter, "ghi", "GHI", emitter_type_int, &i_123,
	    "note_key1", emitter_type_string, &str);
	emitter_kv_note(emitter, "jkl", "JKL", emitter_type_string, &str,
	    "note_key2", emitter_type_bool, &b_false);
	emitter_dict_end(emitter);
	emitter_end(emitter);
}