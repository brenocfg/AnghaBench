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
typedef  char uint8_t ;
struct buf {char* data; size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufprintf (struct buf*,char*,unsigned long) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 int /*<<< orphan*/  isascii (char const) ; 
 scalar_t__ strchr (char const*,char const) ; 
 char tolower (char const) ; 

__attribute__((used)) static void
rndr_header_anchor(struct buf *out, const struct buf *anchor)
{
	static const char *STRIPPED = " -&+$,/:;=?@\"#{}|^~[]`\\*()%.!'";

	const uint8_t *a = anchor->data;
	const size_t size = anchor->size;
	size_t i = 0;
	int stripped = 0, inserted = 0;

	for (; i < size; ++i) {
		// skip html tags
		if (a[i] == '<') {
			while (i < size && a[i] != '>')
				i++;
		// skip html entities
		} else if (a[i] == '&') {
			while (i < size && a[i] != ';')
				i++;
		}
		// replace non-ascii or invalid characters with dashes
		else if (!isascii(a[i]) || strchr(STRIPPED, a[i])) {
			if (inserted && !stripped)
				bufputc(out, '-');
			// and do it only once
			stripped = 1;
		}
		else {
			bufputc(out, tolower(a[i]));
			stripped = 0;
			inserted++;
		}
	}

	// replace the last dash if there was anything added
	if (stripped && inserted)
		out->size--;

	// if anchor found empty, use djb2 hash for it
	if (!inserted && anchor->size) {
	        unsigned long hash = 5381;
		for (i = 0; i < size; ++i) {
			hash = ((hash << 5) + hash) + a[i]; /* h * 33 + c */
		}
		bufprintf(out, "part-%lx", hash);
	}
}