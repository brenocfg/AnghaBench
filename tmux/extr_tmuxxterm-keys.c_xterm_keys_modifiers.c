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
typedef  int u_int ;
typedef  int /*<<< orphan*/  key_code ;

/* Variables and functions */
 int /*<<< orphan*/  KEYC_CTRL ; 
 int /*<<< orphan*/  KEYC_ESCAPE ; 
 int /*<<< orphan*/  KEYC_SHIFT ; 

__attribute__((used)) static int
xterm_keys_modifiers(const char *buf, size_t len, size_t *pos,
    key_code *modifiers)
{
	u_int	flags;

	if (len - *pos < 2)
		return (1);

	if (buf[*pos] < '0' || buf[*pos] > '9')
		return (-1);
	flags = buf[(*pos)++] - '0';
	if (buf[*pos] >= '0' && buf[*pos] <= '9')
		flags = (flags * 10) + (buf[(*pos)++] - '0');
	flags -= 1;

	*modifiers = 0;
	if (flags & 1)
		*modifiers |= KEYC_SHIFT;
	if (flags & 2)
		*modifiers |= KEYC_ESCAPE;
	if (flags & 4)
		*modifiers |= KEYC_CTRL;
	if (flags & 8)
		*modifiers |= KEYC_ESCAPE;
	return (0);
}