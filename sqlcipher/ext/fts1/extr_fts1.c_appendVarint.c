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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_3__ {scalar_t__ nData; scalar_t__ pData; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int VARINT_MAX ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int putVarint (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void appendVarint(DocList *d, sqlite_int64 i){
  char c[VARINT_MAX];
  int n = putVarint(c, i);
  d->pData = realloc(d->pData, d->nData + n);
  memcpy(d->pData + d->nData, c, n);
  d->nData += n;
}