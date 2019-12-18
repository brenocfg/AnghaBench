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
 int /*<<< orphan*/  free (char**) ; 
 char** malloc (int) ; 
 char** realloc (char**,int) ; 

char** strsplit_by_char (char *string, int *length, char c)
{
    char *remainder, *s;
    int size = 8, num = 0, done = 0;
    char **array;
    
    if (string == NULL || string[0] == '\0') {
        *length = 0;
        return NULL;
    }

    array = malloc (sizeof(char *) * size);
    if (array == NULL) {
      return NULL;
    }
    
    remainder = string;
    while (!done) {
        for (s = remainder; *s != c && *s != '\0'; ++s) ;

        if (*s == '\0')
            done = 1;
        else
            *s = '\0';

        array[num++] = remainder;
        if (!done && num == size) {
            size <<= 1;
            char** tmp = realloc (array, sizeof(char *) * size);
            if (tmp == NULL) {
              free(array);
              return NULL;
            }
            array = tmp;
        }

        remainder = s + 1;
    }
    
    if (length != NULL) {
      *length = num;
    }

    return array;
}