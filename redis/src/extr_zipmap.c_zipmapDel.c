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
 unsigned char ZIPMAP_BIGLEN ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,unsigned int) ; 
 unsigned char* zipmapLookupRaw (unsigned char*,unsigned char*,unsigned int,unsigned int*) ; 
 unsigned int zipmapRawEntryLength (unsigned char*) ; 
 unsigned char* zipmapResize (unsigned char*,unsigned int) ; 

unsigned char *zipmapDel(unsigned char *zm, unsigned char *key, unsigned int klen, int *deleted) {
    unsigned int zmlen, freelen;
    unsigned char *p = zipmapLookupRaw(zm,key,klen,&zmlen);
    if (p) {
        freelen = zipmapRawEntryLength(p);
        memmove(p, p+freelen, zmlen-((p-zm)+freelen+1));
        zm = zipmapResize(zm, zmlen-freelen);

        /* Decrease zipmap length */
        if (zm[0] < ZIPMAP_BIGLEN) zm[0]--;

        if (deleted) *deleted = 1;
    } else {
        if (deleted) *deleted = 0;
    }
    return zm;
}