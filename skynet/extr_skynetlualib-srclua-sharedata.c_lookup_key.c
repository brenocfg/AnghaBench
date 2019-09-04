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
typedef  size_t uint32_t ;
struct table {size_t sizehash; struct node* hash; int /*<<< orphan*/  L; } ;
struct node {size_t keyhash; int keytype; int key; size_t next; scalar_t__ nocolliding; } ;

/* Variables and functions */
 int KEYTYPE_INTEGER ; 
 int KEYTYPE_STRING ; 
 char* lua_tolstring (int /*<<< orphan*/ ,int,size_t*) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 

__attribute__((used)) static struct node *
lookup_key(struct table *tbl, uint32_t keyhash, int key, int keytype, const char *str, size_t sz) {
	if (tbl->sizehash == 0)
		return NULL;
	struct node *n = &tbl->hash[keyhash % tbl->sizehash];
	if (keyhash != n->keyhash && n->nocolliding)
		return NULL;
	for (;;) {
		if (keyhash == n->keyhash) {
			if (n->keytype == KEYTYPE_INTEGER) {
				if (keytype == KEYTYPE_INTEGER && n->key == key) {
					return n;
				}
			} else {
				// n->keytype == KEYTYPE_STRING
				if (keytype == KEYTYPE_STRING) {
					size_t sz2 = 0;
					const char * str2 = lua_tolstring(tbl->L, n->key, &sz2);
					if (sz == sz2 && memcmp(str,str2,sz) == 0) {
						return n;
					}
				}
			}
		}
		if (n->next < 0) {
			return NULL;
		}
		n = &tbl->hash[n->next];		
	}
}