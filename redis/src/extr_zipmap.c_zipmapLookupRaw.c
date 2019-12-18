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

/* Variables and functions */
 unsigned char ZIPMAP_END ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,unsigned int) ; 
 unsigned int zipmapDecodeLength (unsigned char*) ; 
 unsigned int zipmapEncodeLength (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static unsigned char *zipmapLookupRaw(unsigned char *zm, unsigned char *key, unsigned int klen, unsigned int *totlen) {
    unsigned char *p = zm+1, *k = NULL;
    unsigned int l,llen;

    while(*p != ZIPMAP_END) {
        unsigned char free;

        /* Match or skip the key */
        l = zipmapDecodeLength(p);
        llen = zipmapEncodeLength(NULL,l);
        if (key != NULL && k == NULL && l == klen && !memcmp(p+llen,key,l)) {
            /* Only return when the user doesn't care
             * for the total length of the zipmap. */
            if (totlen != NULL) {
                k = p;
            } else {
                return p;
            }
        }
        p += llen+l;
        /* Skip the value as well */
        l = zipmapDecodeLength(p);
        p += zipmapEncodeLength(NULL,l);
        free = p[0];
        p += l+1+free; /* +1 to skip the free byte */
    }
    if (totlen != NULL) *totlen = (unsigned int)(p-zm)+1;
    return k;
}