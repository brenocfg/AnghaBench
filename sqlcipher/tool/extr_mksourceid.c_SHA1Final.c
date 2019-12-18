#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* count; int* state; } ;
typedef  TYPE_1__ SHA1Context ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Update (TYPE_1__*,unsigned char const*,int) ; 

__attribute__((used)) static void SHA1Final(unsigned char *digest, SHA1Context *context){
    unsigned int i;
    unsigned char finalcount[8];

    for (i = 0; i < 8; i++) {
        finalcount[i] = (unsigned char)((context->count[(i >= 4 ? 0 : 1)]
         >> ((3-(i & 3)) * 8) ) & 255); /* Endian independent */
    }
    SHA1Update(context, (const unsigned char *)"\200", 1);
    while ((context->count[0] & 504) != 448)
        SHA1Update(context, (const unsigned char *)"\0", 1);
    SHA1Update(context, finalcount, 8);  /* Should cause a SHA1Transform() */

    if (digest) {
        for (i = 0; i < 20; i++)
            digest[i] = (unsigned char)
                ((context->state[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
    }
}