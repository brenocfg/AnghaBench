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
typedef  int /*<<< orphan*/  stream_t ;
typedef  char* gme_err_t ;

/* Variables and functions */
 int vlc_stream_Read (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static gme_err_t ReaderStream (void *data, void *buf, int length)
{
    stream_t *s = data;

    if (vlc_stream_Read (s, buf, length) < length)
        return "short read";
    return NULL;
}