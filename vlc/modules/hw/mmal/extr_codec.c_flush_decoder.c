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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_6__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  input_in_transit; int /*<<< orphan*/  output_in_transit; int /*<<< orphan*/  input; int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_decoder(decoder_t *dec)
{
    decoder_sys_t *sys = dec->p_sys;
    MMAL_BUFFER_HEADER_T *buffer;
    MMAL_STATUS_T status;

    msg_Dbg(dec, "Flushing decoder ports...");
    mmal_port_flush(sys->output);
    mmal_port_flush(sys->input);

    while (atomic_load(&sys->output_in_transit) ||
           atomic_load(&sys->input_in_transit))
        vlc_sem_wait(&sys->sem);
}