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
typedef  int /*<<< orphan*/  sout_stream_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_DecoderDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *id )
{
    (void) p_stream;
    input_DecoderDelete( (decoder_t *)id );
}