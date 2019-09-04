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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ToxAV ;
struct TYPE_2__ {int incoming; } ;
typedef  TYPE_1__ CallControl ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

void t_toxav_call_cb(ToxAV *av, uint32_t friend_number, bool audio_enabled, bool video_enabled, void *user_data)
{
    (void) av;
    (void) friend_number;
    (void) audio_enabled;
    (void) video_enabled;

    printf("Handling CALL callback\n");
    ((CallControl *)user_data)->incoming = true;
}