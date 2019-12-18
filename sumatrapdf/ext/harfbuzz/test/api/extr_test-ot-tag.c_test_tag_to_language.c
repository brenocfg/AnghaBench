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
typedef  int /*<<< orphan*/  hb_tag_t ;
typedef  scalar_t__ hb_language_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_test_message (char*,char const*,char const*) ; 
 scalar_t__ hb_language_from_string (char const*,int) ; 
 scalar_t__ hb_ot_tag_to_language (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_tag_from_string (char const*,int) ; 

__attribute__((used)) static void
test_tag_to_language (const char *tag_s, const char *lang_s)
{
  hb_language_t lang = hb_language_from_string (lang_s, -1);
  hb_tag_t tag = hb_tag_from_string (tag_s, -1);

  g_test_message ("Testing tag %s -> language %s", tag_s, lang_s);

  g_assert (lang == hb_ot_tag_to_language (tag));
}