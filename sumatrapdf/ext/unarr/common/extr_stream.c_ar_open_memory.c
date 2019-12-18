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
struct MemoryStream {size_t length; scalar_t__ offset; void const* data; } ;
typedef  int /*<<< orphan*/  ar_stream ;

/* Variables and functions */
 int /*<<< orphan*/ * ar_open_stream (struct MemoryStream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct MemoryStream* malloc (int) ; 
 int /*<<< orphan*/  memory_close ; 
 int /*<<< orphan*/  memory_read ; 
 int /*<<< orphan*/  memory_seek ; 
 int /*<<< orphan*/  memory_tell ; 

ar_stream *ar_open_memory(const void *data, size_t datalen)
{
    struct MemoryStream *stm = malloc(sizeof(struct MemoryStream));
    if (!stm)
        return NULL;
    stm->data = data;
    stm->length = datalen;
    stm->offset = 0;
    return ar_open_stream(stm, memory_close, memory_read, memory_seek, memory_tell);
}