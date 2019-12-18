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
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 char const* vlc_http_get_token (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vlc_http_msg_get_header (struct vlc_http_msg const*,char const*) ; 

const char *vlc_http_msg_get_token(const struct vlc_http_msg *msg,
                                   const char *field, const char *token)
{
    return vlc_http_get_token(vlc_http_msg_get_header(msg, field), token);
}