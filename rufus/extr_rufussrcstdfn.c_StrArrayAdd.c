#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {char** String; size_t Index; size_t Max; } ;
typedef  TYPE_1__ StrArray ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ realloc (char**,int) ; 
 char* safe_strdup (char const*) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

int32_t StrArrayAdd(StrArray* arr, const char* str, BOOL duplicate)
{
	char** old_table;
	if ((arr == NULL) || (arr->String == NULL) || (str == NULL))
		return -1;
	if (arr->Index == arr->Max) {
		arr->Max *= 2;
		old_table = arr->String;
		arr->String = (char**)realloc(arr->String, arr->Max*sizeof(char*));
		if (arr->String == NULL) {
			free(old_table);
			uprintf("Could not reallocate string array\n");
			return -1;
		}
	}
	arr->String[arr->Index] = (duplicate)?safe_strdup(str):(char*)str;
	if (arr->String[arr->Index] == NULL) {
		uprintf("Could not store string in array\n");
		return -1;
	}
	return arr->Index++;
}