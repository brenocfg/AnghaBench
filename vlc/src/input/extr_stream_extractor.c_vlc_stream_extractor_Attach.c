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

/* Variables and functions */
 int StreamExtractorAttach (int /*<<< orphan*/ **,char const*,char const*) ; 

int
vlc_stream_extractor_Attach( stream_t** source, char const* identifier,
                             char const* module_name )
{
    return StreamExtractorAttach( source, identifier, module_name );
}