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
typedef  int /*<<< orphan*/  Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagSet (int /*<<< orphan*/ *,int) ; 
 int FTS5CSR_REQUIRE_CONTENT ; 
 int FTS5CSR_REQUIRE_DOCSIZE ; 
 int FTS5CSR_REQUIRE_INST ; 
 int FTS5CSR_REQUIRE_POSLIST ; 

__attribute__((used)) static void fts5CsrNewrow(Fts5Cursor *pCsr){
  CsrFlagSet(pCsr, 
      FTS5CSR_REQUIRE_CONTENT 
    | FTS5CSR_REQUIRE_DOCSIZE 
    | FTS5CSR_REQUIRE_INST 
    | FTS5CSR_REQUIRE_POSLIST 
  );
}