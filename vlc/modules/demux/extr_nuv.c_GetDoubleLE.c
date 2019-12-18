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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (double*,void*,int) ; 

__attribute__((used)) static inline void GetDoubleLE( double *pd, void *src )
{
    /* FIXME works only if sizeof(double) == 8 */
#ifdef WORDS_BIGENDIAN
    uint8_t *p = (uint8_t*)pd, *q = (uint8_t*)src;
    int i;
    for( i = 0; i < 8; i++ )
        p[i] = q[7-i];
#else
    memcpy( pd, src, 8 );
#endif
}