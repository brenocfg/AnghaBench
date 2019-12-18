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
struct TYPE_3__ {scalar_t__* zErr; scalar_t__ zIn; scalar_t__ nIn; scalar_t__ bNotFirst; scalar_t__ nLine; scalar_t__ nAlloc; scalar_t__ n; scalar_t__ z; scalar_t__ in; } ;
typedef  TYPE_1__ CsvReader ;

/* Variables and functions */

__attribute__((used)) static void csv_reader_init(CsvReader *p){
  p->in = 0;
  p->z = 0;
  p->n = 0;
  p->nAlloc = 0;
  p->nLine = 0;
  p->bNotFirst = 0;
  p->nIn = 0;
  p->zIn = 0;
  p->zErr[0] = 0;
}