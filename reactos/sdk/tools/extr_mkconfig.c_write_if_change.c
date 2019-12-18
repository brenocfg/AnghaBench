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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 unsigned int fread (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ftell (int /*<<< orphan*/ *) ; 
 unsigned int fwrite (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 char* malloc (unsigned int) ; 
 scalar_t__ memcmp (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int strlen (char*) ; 

int
write_if_change(char* outbuf, char* filename)
{
  FILE* out;
  unsigned int end;
  char* cmpbuf;
  unsigned int stat;

  out = fopen(filename, "rb");
  if (out == NULL)
    {
      out = fopen(filename, "wb");
      if (out == NULL)
	{
	  fprintf(stderr, "Unable to create output file\n");
	  return(1);
	}
      fputs(outbuf, out);
      fclose(out);
      return(0);
    }

  fseek(out, 0, SEEK_END);
  end = ftell(out);
  cmpbuf = malloc(end);
  if (cmpbuf == NULL)
    {
      fprintf(stderr, "Out of memory\n");
      fclose(out);
      return(1);
    }

  fseek(out, 0, SEEK_SET);
  stat = fread(cmpbuf, 1, end, out);
  if (stat != end)
    {
      fprintf(stderr, "Failed to read data\n");
      fclose(out);
      free(cmpbuf);
      return(1);
    }
  if (end == strlen(outbuf) && memcmp(cmpbuf, outbuf, end) == 0)
    {
      fclose(out);
      free(cmpbuf);
      return(0);
    }

  fclose(out);
  free(cmpbuf);
  out = fopen(filename, "wb");
  if (out == NULL)
    {
      fprintf(stderr, "Unable to create output file\n");
      return(1);
    }

  stat = fwrite(outbuf, 1, strlen(outbuf), out);
  if (strlen(outbuf) != stat)
    {
      fprintf(stderr, "Unable to write output file\n");
      fclose(out);
      return(1);
    }
  fclose(out);
  return(0);
}