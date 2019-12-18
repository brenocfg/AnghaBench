#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; scalar_t__ d_type; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char DIR_SEPARATOR_CHAR ; 
 char* DIR_SEPARATOR_STRING ; 
 scalar_t__ DT_REG ; 
 int MAX_PATH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__ f ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  is_valid_file (char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  parse_file (char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_directory (char *path, char *cvspath)
{
  DIR *dirp;
  struct dirent *entry;
  struct stat stbuf;
  char buf[MAX_PATH];
  char newcvspath[MAX_PATH];

#ifdef HAVE_D_TYPE
  dirp = opendir(path);
  if (dirp != NULL)
    {
      while ((entry = readdir(dirp)) != NULL)
        {
          if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; // skip self and parent

      	  if (entry->d_type == DT_REG) // normal file
      	    {
              // Check for an absolute path
              if (path[0] == DIR_SEPARATOR_CHAR)
                {
                  strcpy(buf, path);
                  strcat(buf, DIR_SEPARATOR_STRING);
                  strcat(buf, entry->d_name);
                }
              else
                {
                  if (!getcwd(buf, sizeof(buf)))
                    {
                      printf("Can't get CWD: %s\n", strerror(errno));
                      return;
                    }
                  strcat(buf, DIR_SEPARATOR_STRING);
                  strcat(buf, path);
                  strcat(buf, entry->d_name);
                }

      	      if (stat(buf, &stbuf) == -1)
                {
                  printf("Can't access '%s' (%s)\n", buf, strerror(errno));
                  return;
                }

              if (S_ISDIR(stbuf.st_mode))
          	    {
                  strcpy(newcvspath, cvspath);
                  strcat(newcvspath, f.name);
                  strcat(newcvspath, "/");

                  process_directory(buf, newcvspath);
                  continue;
          	    }

              /* Must be a .c file */
              if (!is_valid_file(buf))
                {
                  continue;
                }

              parse_file(buf, cvspath, entry->d_name);
           }
      }
      closedir(dirp);
    }
  else
    {
      printf("Can't open %s\n", path);
      exit(1);
    }

#else

  dirp = opendir(path);
  if (dirp != NULL)
    {
      while ((entry = readdir(dirp)) != NULL)
      	{
          if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; // skip self and parent

          // Check for an absolute path
          if (path[0] == DIR_SEPARATOR_CHAR)
            {
              strcpy(buf, path);
              strcat(buf, DIR_SEPARATOR_STRING);
              strcat(buf, entry->d_name);
            }
          else
            {
              if (!getcwd(buf, sizeof(buf)))
                {
                  printf("Can't get CWD: %s\n", strerror(errno));
                  return;
                }
              strcat(buf, DIR_SEPARATOR_STRING);
              strcat(buf, path);
              strcat(buf, entry->d_name);
            }

          if (stat(buf, &stbuf) == -1)
            {
              printf("Can't access '%s' (%s)\n", buf, strerror(errno));
              return;
            }

          if (S_ISDIR(stbuf.st_mode))
      	    {
              strcpy(newcvspath, cvspath);
              strcat(newcvspath, entry->d_name);
              strcat(newcvspath, "/");

              process_directory(buf, newcvspath);
              continue;
      	    }

          /* Must be a .c file */
          if (!is_valid_file(buf))
            {
              continue;
            }

          parse_file(buf, cvspath, entry->d_name);
        }
      closedir(dirp);
    }
  else
    {
      printf("Can't open %s\n", path);
      exit(1);
    }

#endif
}