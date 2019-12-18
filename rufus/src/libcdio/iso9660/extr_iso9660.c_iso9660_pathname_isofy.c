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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  tmpbuf ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 

char *
iso9660_pathname_isofy (const char pathname[], uint16_t version)
{
  char tmpbuf[1024] = { 0, };

  cdio_assert (strlen (pathname) < (sizeof (tmpbuf) - sizeof (";65535")));

  snprintf (tmpbuf, sizeof(tmpbuf), "%s;%d", pathname, version);

  return strdup (tmpbuf);
}