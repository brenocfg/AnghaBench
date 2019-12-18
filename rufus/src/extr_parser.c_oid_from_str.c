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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 size_t make_flagged_int (unsigned long,scalar_t__*,size_t) ; 
 scalar_t__* malloc (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static uint8_t* oid_from_str(const char* oid_str, size_t* ret_len)
{
	uint8_t* oid = NULL;
	unsigned long val1 = 0, val;
	const char *endp;
	int arcno = 0;
	size_t oid_len = 0;

	if ((oid_str == NULL) || (oid_str[0] == 0))
		return NULL;

	// We can safely assume that the encoded OID is shorter than the string.
	oid = malloc(1 + strlen(oid_str) + 2);
	if (oid == NULL)
		return NULL;

	do {
		arcno++;
		val = strtoul(oid_str, (char**)&endp, 10);
		if (!isdigit(*oid_str) || !(*endp == '.' || !*endp))
			goto err;
		if (*endp == '.')
			oid_str = endp + 1;

		if (arcno == 1) {
			if (val > 2)
				break; // Not allowed, error caught below.
			val1 = val;
		} else if (arcno == 2) {
			// Need to combine the first two arcs in one byte.
			if (val1 < 2) {
				if (val > 39)
					goto err;
				oid[oid_len++] = (uint8_t)(val1 * 40 + val);
			} else {
				val += 80;
				oid_len = make_flagged_int(val, oid, oid_len);
			}
		} else {
			oid_len = make_flagged_int(val, oid, oid_len);
		}
	} while (*endp == '.');

	// It is not possible to encode only the first arc.
	if (arcno == 1 || oid_len < 2 || oid_len > 254)
		goto err;

	*ret_len = oid_len;
	return oid;

err:
	free(oid);
	return NULL;
}