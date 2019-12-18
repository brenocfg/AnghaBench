#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct reader {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
stream_tell( struct reader *p_reader )
{
    return vlc_stream_Tell( p_reader->u.s );
}