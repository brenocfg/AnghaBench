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
struct chunk_entry {scalar_t__ id; scalar_t__ type; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ FOURCC_LIST ; 
 scalar_t__ FOURCC_RIFF ; 
 int /*<<< orphan*/  debugstr_fourcc (scalar_t__) ; 
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,...) ; 

const char *debugstr_chunk(const struct chunk_entry *chunk)
{
    const char *type = "";

    if (!chunk)
        return "(null)";
    if (chunk->id == FOURCC_RIFF || chunk->id == FOURCC_LIST)
        type = wine_dbg_sprintf("type %s, ", debugstr_fourcc(chunk->type));
    return wine_dbg_sprintf("%s chunk, %ssize %u", debugstr_fourcc(chunk->id), type, chunk->size);
}