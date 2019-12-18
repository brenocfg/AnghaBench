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
struct vlc_input_event {int dummy; } ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  events_data; int /*<<< orphan*/  (* events_cb ) (int /*<<< orphan*/ *,struct vlc_input_event const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ input_thread_private_t ;

/* Variables and functions */
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct vlc_input_event const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void input_SendEvent(input_thread_t *p_input,
                                   const struct vlc_input_event *event)
{
    input_thread_private_t *priv = input_priv(p_input);
    if(priv->events_cb)
        priv->events_cb(p_input, event, priv->events_data);
}