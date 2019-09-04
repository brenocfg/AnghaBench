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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int SetEnv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

int _putenv(const char* val)
{
   int size, result;
   wchar_t *woption;

   size = MultiByteToWideChar(CP_ACP, 0, val, -1, NULL, 0);
   woption = malloc(size* sizeof(wchar_t));
   if (woption == NULL)
      return -1;
   MultiByteToWideChar(CP_ACP, 0, val, -1, woption, size);
   result = SetEnv(woption);
   free(woption);
   return result;
}