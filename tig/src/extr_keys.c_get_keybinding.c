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
struct key {int dummy; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int REQ_NONE ; 
 int REQ_UNKNOWN ; 
 struct keymap const* generic_keymap ; 
 int get_keybinding_in_keymap (struct keymap const*,struct key const*,size_t,int*) ; 
 int /*<<< orphan*/  is_search_keymap (struct keymap const*) ; 

enum request
get_keybinding(const struct keymap *keymap, const struct key key[], size_t keys, int *matches)
{
	enum request request = get_keybinding_in_keymap(keymap, key, keys, matches);

	if (!is_search_keymap(keymap)) {
		int generic_matches = 0;
		enum request generic_request = get_keybinding_in_keymap(generic_keymap, key, keys, &generic_matches);

		/* Include generic matches iff there are more than one
		 * so unbound keys in the current keymap still override
		 * generic keys while still ensuring that the key combo
		 * handler continues to wait for more keys if there is
		 * another possible match. E.g. while in `main` view:
		 *
		 *   bind generic q  quit  # 'q' will quit
		 *   bind main    q  none  # 'q' will do nothing
		 *   bind generic qa quit  # 'qa' will quit
		 *   bind main    qn next  # 'qn' will move to next entry
		 */
		if (matches && (request == REQ_UNKNOWN || generic_matches > 1))
			(*matches) += generic_matches;
		if (request == REQ_UNKNOWN)
			request = generic_request;
	}

	return request == REQ_NONE ? REQ_UNKNOWN : request;
}