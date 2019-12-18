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
struct TYPE_3__ {scalar_t__ errCode; } ;
typedef  int Pgno ;
typedef  TYPE_1__ Pager ;
typedef  int /*<<< orphan*/  DbPage ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int getPageError(
  Pager *pPager,      /* The pager open on the database file */
  Pgno pgno,          /* Page number to fetch */
  DbPage **ppPage,    /* Write a pointer to the page here */
  int flags           /* PAGER_GET_XXX flags */
){
  UNUSED_PARAMETER(pgno);
  UNUSED_PARAMETER(flags);
  assert( pPager->errCode!=SQLITE_OK );
  *ppPage = 0;
  return pPager->errCode;
}