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
struct TYPE_3__ {int /*<<< orphan*/ * hIcon; int /*<<< orphan*/ * lpszFI; } ;
typedef  char TCHAR ;
typedef  TYPE_1__* PDOCBUCKET ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int ExtractIconEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 char* wcsrchr (int /*<<< orphan*/ *,char) ; 

HICON DocGetIcon(PDOCBUCKET pDocBucket)
{
   if (pDocBucket == NULL)
		return NULL;

   if (pDocBucket->hIcon == NULL && pDocBucket->lpszFI != NULL)
   {
      TCHAR *pchT = wcsrchr(pDocBucket->lpszFI, ',');

      if (pchT != NULL)
      {
      	  INT index = atoi(pchT+1);
      	  HICON hIcon;

		  *pchT = '\0';
      	  if (ExtractIconEx(pDocBucket->lpszFI, index, NULL, &hIcon, 1) == 1)
      	  	pDocBucket->hIcon = hIcon;
      }
   }
   return pDocBucket->hIcon;
}