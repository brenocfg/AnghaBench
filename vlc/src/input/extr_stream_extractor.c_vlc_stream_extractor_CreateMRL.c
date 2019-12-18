#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* source; } ;
typedef  TYPE_2__ stream_directory_t ;
struct TYPE_4__ {int /*<<< orphan*/  psz_url; } ;

/* Variables and functions */
 char* StreamExtractorCreateMRL (int /*<<< orphan*/ ,char const*) ; 

char*
vlc_stream_extractor_CreateMRL( stream_directory_t* directory,
                                char const* subentry )
{
    return StreamExtractorCreateMRL( directory->source->psz_url, subentry );
}