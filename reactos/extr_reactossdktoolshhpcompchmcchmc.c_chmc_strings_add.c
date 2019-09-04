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
struct chmcFile {scalar_t__ strings_offset; scalar_t__ strings_len; int /*<<< orphan*/ * strings; } ;
typedef  scalar_t__ UInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

UInt32 chmc_strings_add( struct chmcFile *chm, const char *s)
{
	UInt32 len, off;

	/* FIXME null are errors */

	if (!s || *s == '\0')
		return 0;

	len = strlen(s);

	off = chm->strings_offset;

	if (off + len + 1 < chm->strings_len) {

		memcpy(&chm->strings[off], s, len + 1);
		chm->strings_offset += len + 1;

	} else {
		/* realloc strings */
		/* if the string truncate copy til end of chunk
		   then re-copy from 0 of new */
		BUG_ON("FIXME: %s: %d: handle more chunk for strings\n",
		       __FILE__, __LINE__);
	}

	return off;
}