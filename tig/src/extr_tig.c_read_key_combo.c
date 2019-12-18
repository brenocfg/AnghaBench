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
struct keymap {int dummy; } ;
struct key_combo {int member_0; int request; int /*<<< orphan*/  member_2; struct keymap* member_1; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int REQ_NONE ; 
 int /*<<< orphan*/  key_combo_handler ; 
 char* read_prompt_incremental (char*,int,int,int /*<<< orphan*/ ,struct key_combo*) ; 

enum request
read_key_combo(struct keymap *keymap)
{
	struct key_combo combo = { REQ_NONE, keymap, 0 };
	char *value = read_prompt_incremental("", false, false, key_combo_handler, &combo);

	return value ? combo.request : REQ_NONE;
}