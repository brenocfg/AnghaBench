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
typedef  size_t HttpError ;

/* Variables and functions */
 char const** http_error_strings ; 

const char *
ts_http_strerror(HttpError http_errno)
{
	return http_error_strings[http_errno];
}