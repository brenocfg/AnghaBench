#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  footer; } ;
typedef  TYPE_1__ vlc_logger_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void Close(void *opaque)
{
    vlc_logger_sys_t *sys = opaque;

    fputs(sys->footer, sys->stream);
    fclose(sys->stream);
    free(sys);
}