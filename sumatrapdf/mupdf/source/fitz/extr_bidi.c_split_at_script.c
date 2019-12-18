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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  (* fz_bidi_fragment_fn ) (int /*<<< orphan*/  const*,size_t,int,int,void*) ;

/* Variables and functions */
 int UCDN_SCRIPT_COMMON ; 
 int UCDN_SCRIPT_INHERITED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,size_t,int,int,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*,size_t,int,int,void*) ; 
 int ucdn_get_script (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
split_at_script(const uint32_t *fragment,
		size_t fragment_len,
		int level,
		void *arg,
		fz_bidi_fragment_fn *callback)
{
	int script = UCDN_SCRIPT_COMMON;
	size_t script_start, i;

	script_start = 0;
	for (i = 0; i < fragment_len; i++)
	{
		int s = ucdn_get_script(fragment[i]);
		if (s == UCDN_SCRIPT_COMMON || s == UCDN_SCRIPT_INHERITED)
		{
			/* Punctuation etc. This is fine. */
		}
		else if (s == script)
		{
			/* Same script. Still fine. */
		}
		else if (script == UCDN_SCRIPT_COMMON || script == UCDN_SCRIPT_INHERITED)
		{
			/* First non punctuation thing. Set the script. */
			script = s;
		}
		else
		{
			/* Change of script. Break the fragment. */
			(*callback)(&fragment[script_start], i - script_start, level, script, arg);
			script_start = i;
			script = s;
		}
	}
	if (script_start != fragment_len)
	{
		(*callback)(&fragment[script_start], fragment_len - script_start, level, script, arg);
	}
}