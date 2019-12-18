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
typedef  size_t uint8_t ;

/* Variables and functions */
 char* compat_strdup (char const*) ; 
 size_t* cp1252_utf8 ; 
 int /*<<< orphan*/  free (size_t*) ; 
 scalar_t__ is_utf8 (char const*) ; 
 size_t* malloc (size_t) ; 
 char* realloc (size_t*,size_t) ; 
 int strlen (char const*) ; 
 size_t* tblofs ; 

char *
icy2utf8(const char *src, int force)
{
	const uint8_t *s = (const uint8_t *)src;
	size_t srclen, dstlen, i, k;
	uint8_t ch, *d;
	char *dst;

	/* Some funny streams from Apple/iTunes give ICY info in UTF-8 already.
	   So, be prepared and don't try to re-encode such. Unless forced. */
	if(!force && is_utf8(src)) return (compat_strdup(src));

	srclen = strlen(src) + 1;
	/* allocate conservatively */
	if ((d = malloc(srclen * 3)) == NULL)
		return (NULL);

	i = 0;
	dstlen = 0;
	while (i < srclen) {
		ch = s[i++];
		k = tblofs[ch];
		while (k < tblofs[ch + 1])
			d[dstlen++] = cp1252_utf8[k++];
	}

	/* dstlen includes trailing NUL since srclen also does */
	if ((dst = realloc(d, dstlen)) == NULL) {
		free(d);
		return (NULL);
	}
	return (dst);
}