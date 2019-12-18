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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 

__attribute__((used)) static input_item_t *
CreateDummyMedia(int num)
{
    char *url;
    char *name;

    int res = asprintf(&url, "vlc://item-%d", num);
    if (res == -1)
        return NULL;

    res = asprintf(&name, "item-%d", num);
    if (res == -1)
        return NULL;

    input_item_t *media = input_item_New(url, name);
    free(url);
    free(name);
    return media;
}