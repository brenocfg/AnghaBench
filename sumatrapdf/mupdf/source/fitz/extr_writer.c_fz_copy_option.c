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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

int
fz_copy_option(fz_context *ctx, const char *val, char *dest, size_t maxlen)
{
	const char *e = val;
	size_t len, len2;

	if (val == NULL) {
		if (maxlen)
			*dest = 0;
		return 0;
	}

	while (*e != ',' && *e != 0)
		e++;

	len = e-val;
	len2 = len+1; /* Allow for terminator */
	if (len > maxlen)
		len = maxlen;
	memcpy(dest, val, len);
	if (len < maxlen)
		memset(dest+len, 0, maxlen-len);

	return len2 >= maxlen ? len2 - maxlen : 0;
}