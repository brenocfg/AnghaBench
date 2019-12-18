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
typedef  int /*<<< orphan*/  uint_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  conn_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vlc_h2_frame_data (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stream_data(uint_fast32_t id, const char *str, bool eos)
{
    conn_send(vlc_h2_frame_data(id, str, strlen(str), eos));
}