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
struct _Locale_name_hint {int dummy; } ;
struct _Locale_messages {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_MESSAGES_MASK ; 
 int _STLP_LOC_UNKNOWN_NAME ; 
 scalar_t__ newlocale (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

struct _Locale_messages *_Locale_messages_create(const char *nm, struct _Locale_name_hint* hint,
                                                 int *__err_code) {
  *__err_code = _STLP_LOC_UNKNOWN_NAME;
  return (struct _Locale_messages*)newlocale(LC_MESSAGES_MASK, nm, NULL);
}