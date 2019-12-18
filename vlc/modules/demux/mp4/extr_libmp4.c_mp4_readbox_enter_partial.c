#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {scalar_t__ i_size; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mp4_readbox_enter_common (int /*<<< orphan*/ *,TYPE_1__*,size_t,void (*) (TYPE_1__*),scalar_t__) ; 

__attribute__((used)) static uint8_t *mp4_readbox_enter_partial( stream_t *s, MP4_Box_t *box,
                                           size_t typesize,
                                           void (*release)( MP4_Box_t * ),
                                           uint64_t *restrict readsize )
{
    if( (uint64_t)*readsize > box->i_size )
        *readsize = box->i_size;

    return mp4_readbox_enter_common( s, box, typesize, release, *readsize );
}