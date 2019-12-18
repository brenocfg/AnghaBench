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
typedef  int uint64_t ;

/* Variables and functions */
 int SSIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 size_t strnlen (char const*,int) ; 

__attribute__((used)) static char *mp4_getstringz( uint8_t **restrict in, uint64_t *restrict size )
{
    assert( *size <= SSIZE_MAX );

    if( *size == 0 )
        return NULL;

    if( *in == 0 ) /* Null string stored */
    {
        *in += 1;
        *size -= 1;
        return NULL;
    }

    size_t len = strnlen( (const char *)*in, *size );
    if( len == 0 || len >= *size )
        return NULL;

    len++;

    char *ret = malloc( len );
    if( likely(ret != NULL) )
        memcpy( ret, *in, len );
    *in += len;
    *size -= len;
    return ret;
}