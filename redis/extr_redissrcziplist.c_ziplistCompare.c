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
struct TYPE_3__ {unsigned int len; int headersize; int /*<<< orphan*/  encoding; } ;
typedef  TYPE_1__ zlentry ;

/* Variables and functions */
 unsigned char ZIP_END ; 
 scalar_t__ ZIP_IS_STR (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  zipEntry (unsigned char*,TYPE_1__*) ; 
 long long zipLoadInteger (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zipTryEncoding (unsigned char*,unsigned int,long long*,unsigned char*) ; 

unsigned int ziplistCompare(unsigned char *p, unsigned char *sstr, unsigned int slen) {
    zlentry entry;
    unsigned char sencoding;
    long long zval, sval;
    if (p[0] == ZIP_END) return 0;

    zipEntry(p, &entry);
    if (ZIP_IS_STR(entry.encoding)) {
        /* Raw compare */
        if (entry.len == slen) {
            return memcmp(p+entry.headersize,sstr,slen) == 0;
        } else {
            return 0;
        }
    } else {
        /* Try to compare encoded values. Don't compare encoding because
         * different implementations may encoded integers differently. */
        if (zipTryEncoding(sstr,slen,&sval,&sencoding)) {
          zval = zipLoadInteger(p+entry.headersize,entry.encoding);
          return zval == sval;
        }
    }
    return 0;
}