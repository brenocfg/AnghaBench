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
struct Tox {int dummy; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  group_chat_object; } ;
typedef  TYPE_1__ Messenger ;

/* Variables and functions */
 int group_send_audio (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

int toxav_group_send_audio(struct Tox *tox, int groupnumber, const int16_t *pcm, unsigned int samples, uint8_t channels,
                           unsigned int sample_rate)
{
    Messenger *m = (Messenger *)tox;
    return group_send_audio(m->group_chat_object, groupnumber, pcm, samples, channels, sample_rate);
}