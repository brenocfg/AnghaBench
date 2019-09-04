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
struct encoding {scalar_t__ cd; struct encoding* next; int /*<<< orphan*/  fromcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODING_UTF8 ; 
 scalar_t__ ICONV_NONE ; 
 struct encoding* calloc (int,int) ; 
 struct encoding* encodings ; 
 int /*<<< orphan*/  free (struct encoding*) ; 
 scalar_t__ iconv_open (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,size_t) ; 

struct encoding *
encoding_open(const char *fromcode)
{
	struct encoding *encoding;
	size_t len = strlen(fromcode);

	if (!*fromcode)
		return NULL;

	for (encoding = encodings; encoding; encoding = encoding->next) {
		if (!strcasecmp(encoding->fromcode, fromcode))
			return encoding;
	}

	encoding = calloc(1, sizeof(*encoding) + len);
	strncpy(encoding->fromcode, fromcode, len);
	encoding->cd = iconv_open(ENCODING_UTF8, fromcode);
	if (encoding->cd == ICONV_NONE) {
		free(encoding);
		return NULL;
	}

	encoding->next = encodings;
	encodings = encoding;

	return encoding;
}