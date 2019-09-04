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
struct chunk_entry {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_get_chunk (int /*<<< orphan*/ *,struct chunk_entry*) ; 
 int /*<<< orphan*/  stream_skip_chunk (int /*<<< orphan*/ *,struct chunk_entry*) ; 

HRESULT stream_next_chunk(IStream *stream, struct chunk_entry *chunk)
{
    HRESULT hr;

    if (chunk->id) {
        hr = stream_skip_chunk(stream, chunk);
        if (FAILED(hr))
            return hr;
    }

    return stream_get_chunk(stream, chunk);
}