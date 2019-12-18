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
struct vlc_memstream {size_t length; char* ptr; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  add_overflow (size_t,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

size_t vlc_memstream_write(struct vlc_memstream *ms, const void *ptr,
                           size_t len)
{
    size_t newlen;

    if (unlikely(add_overflow(ms->length, len, &newlen))
     || unlikely(add_overflow(newlen, 1, &newlen)))
        goto error;

    char *base = realloc(ms->ptr, newlen);
    if (unlikely(base == NULL))
        goto error;

    memcpy(base + ms->length, ptr, len);
    ms->ptr = base;
    ms->length += len;
    base[ms->length] = '\0';
    return len;

error:
    ms->error = EOF;
    return 0;
}