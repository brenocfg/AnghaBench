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
struct state {unsigned int left; unsigned char* in; int first; scalar_t__ next; int /*<<< orphan*/  out; void* outhow; scalar_t__ (* outfun ) (void*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  env; scalar_t__ bitcnt; scalar_t__ bitbuf; void* inhow; int /*<<< orphan*/  infun; } ;
typedef  scalar_t__ (* blast_out ) (void*,int /*<<< orphan*/ ,scalar_t__) ;
typedef  int /*<<< orphan*/  blast_in ;

/* Variables and functions */
 int decomp (struct state*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ ,scalar_t__) ; 

int blast(blast_in infun, void *inhow, blast_out outfun, void *outhow,
          unsigned *left, unsigned char **in)
{
    struct state s;             /* input/output state */
    int err;                    /* return value */

    /* initialize input state */
    s.infun = infun;
    s.inhow = inhow;
    if (left != NULL && *left) {
        s.left = *left;
        s.in = *in;
    }
    else
        s.left = 0;
    s.bitbuf = 0;
    s.bitcnt = 0;

    /* initialize output state */
    s.outfun = outfun;
    s.outhow = outhow;
    s.next = 0;
    s.first = 1;

    /* return if bits() or decode() tries to read past available input */
    if (setjmp(s.env) != 0)             /* if came back here via longjmp(), */
        err = 2;                        /*  then skip decomp(), return error */
    else
        err = decomp(&s);               /* decompress */

    /* return unused input */
    if (left != NULL)
        *left = s.left;
    if (in != NULL)
        *in = s.left ? s.in : NULL;

    /* write any leftover output and update the error code if needed */
    if (err != 1 && s.next && s.outfun(s.outhow, s.out, s.next) && err == 0)
        err = 1;
    return err;
}