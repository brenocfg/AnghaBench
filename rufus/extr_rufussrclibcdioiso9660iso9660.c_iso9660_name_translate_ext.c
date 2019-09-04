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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ isupper (unsigned char) ; 
 int strlen (char const*) ; 
 unsigned char tolower (unsigned char) ; 

int
iso9660_name_translate_ext(const char *psz_oldname, char *psz_newname,
                           uint8_t u_joliet_level)
{
  int len = strlen(psz_oldname);
  int i;

  if (0 == len) return 0;
  for (i = 0; i < len; i++) {
    unsigned char c = psz_oldname[i];
    if (!c)
      break;

    /* Lower case, unless we have Joliet extensions.  */
    if (!u_joliet_level && isupper(c)) c = tolower(c);

    /* Drop trailing '.;1' (ISO 9660:1988 7.5.1 requires period) */
    if (c == '.' && i == len - 3
        && psz_oldname[i + 1] == ';' && psz_oldname[i + 2] == '1')
      break;

    /* Drop trailing ';1' */
    if (c == ';' && i == len - 2 && psz_oldname[i + 1] == '1')
      break;

    /* Convert remaining ';' to '.' */
    if (c == ';')
      c = '.';

    psz_newname[i] = c;
  }
  psz_newname[i] = '\0';
  return i;
}