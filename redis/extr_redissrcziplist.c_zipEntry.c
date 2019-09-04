#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int prevrawlensize; int lensize; int headersize; unsigned char* p; int /*<<< orphan*/  len; int /*<<< orphan*/  encoding; int /*<<< orphan*/  prevrawlen; } ;
typedef  TYPE_1__ zlentry ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_DECODE_LENGTH (unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIP_DECODE_PREVLEN (unsigned char*,int,int /*<<< orphan*/ ) ; 

void zipEntry(unsigned char *p, zlentry *e) {

    ZIP_DECODE_PREVLEN(p, e->prevrawlensize, e->prevrawlen);
    ZIP_DECODE_LENGTH(p + e->prevrawlensize, e->encoding, e->lensize, e->len);
    e->headersize = e->prevrawlensize + e->lensize;
    e->p = p;
}