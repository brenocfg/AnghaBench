#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flv_header; int /*<<< orphan*/  flv_header_len; } ;
typedef  TYPE_1__ stream_sys_t ;
struct TYPE_6__ {int /*<<< orphan*/  metadata_len; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ hds_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  write_flv_header_and_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void initialize_header_and_metadata( stream_sys_t* p_sys, hds_stream_t *stream )
{
    p_sys->flv_header_len =
        write_flv_header_and_metadata( &p_sys->flv_header, stream->metadata,
                                       stream->metadata_len );
}