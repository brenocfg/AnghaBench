#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int isReadable; int hasError; int /*<<< orphan*/  isQuiet; } ;
struct TYPE_4__ {TYPE_1__ file; int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  THFile ;
typedef  TYPE_2__ THDiskFile ;

/* Variables and functions */
 size_t TBRS_BSZ ; 
 char* THAlloc (size_t) ; 
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 
 int /*<<< orphan*/  THError (char*) ; 
 int /*<<< orphan*/  THFree (char*) ; 
 char* THRealloc (char*,size_t) ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static size_t THDiskFile_readString(THFile *self, const char *format, char **str_)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file");
  THArgCheck((strlen(format) >= 2 ? (format[0] == '*') && (format[1] == 'a' || format[1] == 'l') : 0), 2, "format must be '*a' or '*l'");

/* note: the string won't survive long, as it is copied into lua */
/* so 1024 is not that big... */
#define TBRS_BSZ 1024L

  if(format[1] == 'a')
  {
    char *p = THAlloc(TBRS_BSZ);
    size_t total = TBRS_BSZ;
    size_t pos = 0;

    for (;;)
    {
      if(total-pos == 0) /* we need more space! */
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      pos += fread(p+pos, 1, total-pos, dfself->handle);
      if (pos < total) /* eof? */
      {
        if(pos == 0)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
    }
  }
  else
  {
    char *p = THAlloc(TBRS_BSZ);
    size_t total = TBRS_BSZ;
    size_t pos = 0;
    size_t size;

    for (;;)
    {
      if(total-pos <= 1) /* we can only write '\0' in there! */
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      if (fgets(p+pos, total-pos, dfself->handle) == NULL) /* eof? */
      {
        if(pos == 0)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
      size = strlen(p+pos);
      if (size == 0 || (p+pos)[size-1] != '\n')
      {
        pos += size;
      }
      else
      {
        pos += size-1; /* do not include `eol' */
        *str_ = p;
        return pos;
      }
    }
  }

  *str_ = NULL;
  return 0;
}