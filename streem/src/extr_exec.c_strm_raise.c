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
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ERROR_RUNTIME ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strm_set_exc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_new (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_value (int /*<<< orphan*/ ) ; 

void
strm_raise(strm_stream* strm, const char* msg)
{
  if (!strm) return;
  strm_set_exc(strm, NODE_ERROR_RUNTIME,
               strm_str_value(strm_str_new(msg, strlen(msg))));
}