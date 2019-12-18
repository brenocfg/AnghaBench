#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite_int64 ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  term; } ;
typedef  TYPE_1__ InteriorBlock ;

/* Variables and functions */
 int /*<<< orphan*/  INTERIOR_MAX ; 
 int VARINT_MAX ; 
 int /*<<< orphan*/  dataBufferInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataBufferReplace (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int putVarint (char*,int) ; 
 TYPE_1__* sqlite3_malloc (int) ; 

__attribute__((used)) static InteriorBlock *interiorBlockNew(int iHeight, sqlite_int64 iChildBlock,
                                       const char *pTerm, int nTerm){
  InteriorBlock *block = sqlite3_malloc(sizeof(InteriorBlock));
  char c[VARINT_MAX+VARINT_MAX];
  int n;

  if( block ){
    memset(block, 0, sizeof(*block));
    dataBufferInit(&block->term, 0);
    dataBufferReplace(&block->term, pTerm, nTerm);

    n = putVarint(c, iHeight);
    n += putVarint(c+n, iChildBlock);
    dataBufferInit(&block->data, INTERIOR_MAX);
    dataBufferReplace(&block->data, c, n);
  }
  return block;
}