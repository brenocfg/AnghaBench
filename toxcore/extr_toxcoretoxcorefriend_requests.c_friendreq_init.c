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
typedef  int /*<<< orphan*/  Friend_Requests ;
typedef  int /*<<< orphan*/  Friend_Connections ;

/* Variables and functions */
 int /*<<< orphan*/  friendreq_handlepacket ; 
 int /*<<< orphan*/  set_friend_request_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void friendreq_init(Friend_Requests *fr, Friend_Connections *fr_c)
{
    set_friend_request_callback(fr_c, &friendreq_handlepacket, fr);
}