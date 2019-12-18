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
typedef  int uint32_t ;

/* Variables and functions */
 void* GetDWLE (char*) ; 
 int /*<<< orphan*/  SetDWLE (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int comment_add(char **comments, size_t *length, const char *tag,
                       const char *val)
{
    char *p = *comments;
    uint32_t vendor_length = GetDWLE(p + 8);
    size_t user_comment_list_length = GetDWLE(p + 8 + 4 + vendor_length);
    size_t tag_len = (tag ? strlen(tag) : 0);
    size_t val_len = strlen(val);
    size_t len = (*length) + 4 + tag_len + val_len;

    char *reaced = realloc(p, len);
    if (reaced == NULL)
        return 1;
    p = reaced;

    SetDWLE(p + *length, tag_len + val_len);          /* length of comment */
    if (tag) memcpy(p + *length + 4, tag, tag_len);         /* comment */
    memcpy(p + *length + 4 + tag_len, val, val_len);        /* comment */
    SetDWLE(p + 8 + 4 + vendor_length, user_comment_list_length + 1);
    *comments = p;
    *length = len;
    return 0;
}