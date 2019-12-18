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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* memrchr (char*,char,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *vlc_uri_remove_dot_segments(char *str)
{
    char *input = str, *output = str;

    while (input[0] != '\0')
    {
        assert(output <= input);

        if (strncmp(input, "../", 3) == 0)
        {
            input += 3;
            continue;
        }
        if (strncmp(input, "./", 2) == 0)
        {
            input += 2;
            continue;
        }
        if (strncmp(input, "/./", 3) == 0)
        {
            input += 2;
            continue;
        }
        if (strcmp(input, "/.") == 0)
        {
            input[1] = '\0';
            continue;
        }
        if (strncmp(input, "/../", 4) == 0)
        {
            input += 3;
            output = memrchr(str, '/', output - str);
            if (output == NULL)
                output = str;
            continue;
        }
        if (strcmp(input, "/..") == 0)
        {
            input[1] = '\0';
            output = memrchr(str, '/', output - str);
            if (output == NULL)
                output = str;
            continue;
        }
        if (strcmp(input, ".") == 0)
        {
            input++;
            continue;
        }
        if (strcmp(input, "..") == 0)
        {
            input += 2;
            continue;
        }

        if (input[0] == '/')
            *(output++) = *(input++);

        size_t len = strcspn(input, "/");

        if (input != output)
            memmove(output, input, len);

        input += len;
        output += len;
    }

    output[0] = '\0';
    return str;
}