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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;
struct reader {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,size_t) ; 

__attribute__((used)) static ssize_t
stream_peek( struct reader *p_reader, const uint8_t **pp_buf, size_t i_len )
{
    return vlc_stream_Peek( p_reader->u.s, pp_buf, i_len );
}