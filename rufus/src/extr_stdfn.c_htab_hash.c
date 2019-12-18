#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int size; int filled; TYPE_1__* table; } ;
typedef  TYPE_2__ htab_table ;
struct TYPE_4__ {int used; char* str; } ;

/* Variables and functions */
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 scalar_t__ safe_strcmp (char*,char*) ; 
 scalar_t__ safe_strlen (char*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

uint32_t htab_hash(char* str, htab_table* htab)
{
	uint32_t hval, hval2;
	uint32_t idx;
	uint32_t r = 0;
	int c;
	char* sz = str;

	if ((htab == NULL) || (htab->table == NULL) || (str == NULL)) {
		return 0;
	}

	// Compute main hash value using sdbm's algorithm (empirically
	// shown to produce half the collisions as djb2's).
	// See http://www.cse.yorku.ca/~oz/hash.html
	while ((c = *sz++) != 0)
		r = c + (r << 6) + (r << 16) - r;
	if (r == 0)
		++r;

	// compute table hash: simply take the modulus
	hval = r % htab->size;
	if (hval == 0)
		++hval;

	// Try the first index
	idx = hval;

	if (htab->table[idx].used) {
		if ( (htab->table[idx].used == hval)
		  && (safe_strcmp(str, htab->table[idx].str) == 0) ) {
			// existing hash
			return idx;
		}
		// uprintf("hash collision ('%s' vs '%s')\n", str, htab->table[idx].str);

		// Second hash function, as suggested in [Knuth]
		hval2 = 1 + hval % (htab->size - 2);

		do {
			// Because size is prime this guarantees to step through all available indexes
			if (idx <= hval2) {
				idx = ((uint32_t)htab->size) + idx - hval2;
			} else {
				idx -= hval2;
			}

			// If we visited all entries leave the loop unsuccessfully
			if (idx == hval) {
				break;
			}

			// If entry is found use it.
			if ( (htab->table[idx].used == hval)
			  && (safe_strcmp(str, htab->table[idx].str) == 0) ) {
				return idx;
			}
		}
		while (htab->table[idx].used);
	}

	// Not found => New entry

	// If the table is full return an error
	if (htab->filled >= htab->size) {
		uprintf("hash table is full (%d entries)", htab->size);
		return 0;
	}

	safe_free(htab->table[idx].str);
	htab->table[idx].used = hval;
	htab->table[idx].str = (char*) malloc(safe_strlen(str)+1);
	if (htab->table[idx].str == NULL) {
		uprintf("could not duplicate string for hash table\n");
		return 0;
	}
	memcpy(htab->table[idx].str, str, safe_strlen(str)+1);
	++htab->filled;

	return idx;
}