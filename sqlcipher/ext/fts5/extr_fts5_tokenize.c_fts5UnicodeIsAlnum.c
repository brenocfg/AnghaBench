#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int* aCategory; } ;
typedef  TYPE_1__ Unicode61Tokenizer ;

/* Variables and functions */
 int fts5UnicodeIsException (TYPE_1__*,int) ; 
 size_t sqlite3Fts5UnicodeCategory (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5UnicodeIsAlnum(Unicode61Tokenizer *p, int iCode){
  return (
    p->aCategory[sqlite3Fts5UnicodeCategory((u32)iCode)]
    ^ fts5UnicodeIsException(p, iCode)
  );
}