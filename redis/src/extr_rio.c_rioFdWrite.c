#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_5__ {size_t pos; scalar_t__ buf; int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
struct TYPE_7__ {TYPE_2__ io; } ;
typedef  TYPE_3__ rio ;

/* Variables and functions */
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ EWOULDBLOCK ; 
 size_t PROTO_IOBUF_LEN ; 
 scalar_t__ errno ; 
 scalar_t__ sdscatlen (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  sdsclear (scalar_t__) ; 
 size_t sdslen (scalar_t__) ; 
 int write (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static size_t rioFdWrite(rio *r, const void *buf, size_t len) {
    ssize_t retval;
    unsigned char *p = (unsigned char*) buf;
    int doflush = (buf == NULL && len == 0);

    /* For small writes, we rather keep the data in user-space buffer, and flush
     * it only when it grows. however for larger writes, we prefer to flush
     * any pre-existing buffer, and write the new one directly without reallocs
     * and memory copying. */
    if (len > PROTO_IOBUF_LEN) {
        /* First, flush any pre-existing buffered data. */
        if (sdslen(r->io.fd.buf)) {
            if (rioFdWrite(r, NULL, 0) == 0)
                return 0;
        }
        /* Write the new data, keeping 'p' and 'len' from the input. */
    } else {
        if (len) {
            r->io.fd.buf = sdscatlen(r->io.fd.buf,buf,len);
            if (sdslen(r->io.fd.buf) > PROTO_IOBUF_LEN)
                doflush = 1;
            if (!doflush)
                return 1;
        }
        /* Flusing the buffered data. set 'p' and 'len' accordintly. */
        p = (unsigned char*) r->io.fd.buf;
        len = sdslen(r->io.fd.buf);
    }

    size_t nwritten = 0;
    while(nwritten != len) {
        retval = write(r->io.fd.fd,p+nwritten,len-nwritten);
        if (retval <= 0) {
            /* With blocking io, which is the sole user of this
             * rio target, EWOULDBLOCK is returned only because of
             * the SO_SNDTIMEO socket option, so we translate the error
             * into one more recognizable by the user. */
            if (retval == -1 && errno == EWOULDBLOCK) errno = ETIMEDOUT;
            return 0; /* error. */
        }
        nwritten += retval;
    }

    r->io.fd.pos += len;
    sdsclear(r->io.fd.buf);
    return 1;
}