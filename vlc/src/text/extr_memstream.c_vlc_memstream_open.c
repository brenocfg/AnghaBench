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
struct vlc_memstream {int error; scalar_t__ length; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int vlc_memstream_open(struct vlc_memstream *ms)
{
    ms->error = 0;
    ms->ptr = calloc(1, 1);
    if (unlikely(ms->ptr == NULL))
        ms->error = EOF;
    ms->length = 0;
    return ms->error;
}