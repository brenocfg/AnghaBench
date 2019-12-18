#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int multibytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  bytes; } ;
struct key {TYPE_2__ modifiers; TYPE_1__ data; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int SUCCESS ; 
 int error (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int success (char*,int,char const*) ; 
 size_t utf8_char_length (char const*) ; 
 scalar_t__ utf8_to_unicode (char const*,size_t) ; 

__attribute__((used)) static enum status_code
parse_key_value(struct key *key, const char **name_ptr, size_t offset,
		const char *replacement, const char *end)
{
	const char *name = replacement ? replacement : *name_ptr + offset;
	size_t namelen = utf8_char_length(name);
	const char *nameend = name + namelen;

	if (strlen(name) < namelen || utf8_to_unicode(name, namelen) == 0)
		return error("Error parsing UTF-8 bytes: %s", name);

	strncpy(key->data.bytes, name, namelen);
	key->modifiers.multibytes = 1;
	if (end) {
		*name_ptr = end + 1;
		if (!replacement && nameend + 1 < end)
			return success("Ignoring text after key mapping: %.*s",
				(int) (end - nameend), nameend);
	} else {
		*name_ptr = nameend;
	}

	return SUCCESS;
}