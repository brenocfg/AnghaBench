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
typedef  int /*<<< orphan*/  vlc_stream_fifo_t ;
struct vlc_stream_fifo_private {int /*<<< orphan*/ * writer; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 struct vlc_stream_fifo_private* vlc_stream_Private (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_stream_fifo_t *vlc_stream_fifo_Writer(stream_t *s)
{
    struct vlc_stream_fifo_private *sys = vlc_stream_Private(s);

    return sys->writer;
}