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

/* Variables and functions */
 int BUFMAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned char,unsigned char,char*) ; 
 char getDebugChar () ; 
 unsigned char hex (char) ; 
 int /*<<< orphan*/  putDebugChar (char) ; 
 char* remcomInBuffer ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  stderr ; 

char *
getpacket (void)
{
  char *buffer = &remcomInBuffer[0];
  unsigned char checksum;
  unsigned char xmitcsum;
  int count;
  char ch;

  while (1)
	{
	  /* wait around for the start character, ignore all other characters */
	  while ((ch = getDebugChar ()) != '$')
		;

	retry:
	  checksum = 0;
	  xmitcsum = -1;
	  count = 0;

	  /* now, read until a # or end of buffer is found */
	  while (count < BUFMAX - 1)
		{
		  ch = getDebugChar ();
		  if (ch == '$')
			goto retry;
		  if (ch == '#')
			break;
		  checksum = checksum + ch;
		  buffer[count] = ch;
		  count = count + 1;
		}
	  buffer[count] = 0;

	  if (ch == '#')
		{
		  ch = getDebugChar ();
		  xmitcsum = hex (ch) << 4;
		  ch = getDebugChar ();
		  xmitcsum += hex (ch);

		  if (checksum != xmitcsum)
			{
			  if (remote_debug)
				{
				  fprintf (stderr,
						   "bad checksum.  My count = 0x%x, sent=0x%x. buf=%s\n",
						   checksum, xmitcsum, buffer);
				}
			  putDebugChar ('-');		/* failed checksum */
			}
		  else
			{
			  putDebugChar ('+');		/* successful transfer */

			  /* if a sequence char is present, reply the sequence ID */
			  if (buffer[2] == ':')
				{
				  putDebugChar (buffer[0]);
				  putDebugChar (buffer[1]);

				  return &buffer[3];
				}

			  return &buffer[0];
			}
		}
	}
}