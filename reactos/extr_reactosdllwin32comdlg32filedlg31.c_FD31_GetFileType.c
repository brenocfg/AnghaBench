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
typedef  int WORD ;
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 scalar_t__ FILE_star ; 
 int lstrlenW (scalar_t__) ; 

__attribute__((used)) static LPCWSTR FD31_GetFileType(LPCWSTR cfptr, LPCWSTR fptr, const WORD index)
{
  int n, i;
  i = 0;
  if (cfptr)
    for ( ;(n = lstrlenW(cfptr)) != 0; i++)
      {
	cfptr += n + 1;
	if (i == index)
	  return cfptr;
	cfptr += lstrlenW(cfptr) + 1;
      }
  if (fptr)
    for ( ;(n = lstrlenW(fptr)) != 0; i++)
      {
	fptr += n + 1;
	if (i == index)
	  return fptr;
	fptr += lstrlenW(fptr) + 1;
    }
  return FILE_star; /* FIXME */
}