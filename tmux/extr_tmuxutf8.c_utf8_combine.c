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
typedef  int /*<<< orphan*/  wchar_t ;
struct utf8_data {int /*<<< orphan*/ * data; scalar_t__ size; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 scalar_t__ MB_CUR_MAX ; 
 int UTF8_DONE ; 
 int UTF8_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_debug (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbtowc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

enum utf8_state
utf8_combine(const struct utf8_data *ud, wchar_t *wc)
{
#ifdef HAVE_UTF8PROC
	switch (utf8proc_mbtowc(wc, ud->data, ud->size)) {
#else
	switch (mbtowc(wc, ud->data, ud->size)) {
#endif
	case -1:
		log_debug("UTF-8 %.*s, mbtowc() %d", (int)ud->size, ud->data,
		    errno);
		mbtowc(NULL, NULL, MB_CUR_MAX);
		return (UTF8_ERROR);
	case 0:
		return (UTF8_ERROR);
	default:
		return (UTF8_DONE);
	}
}