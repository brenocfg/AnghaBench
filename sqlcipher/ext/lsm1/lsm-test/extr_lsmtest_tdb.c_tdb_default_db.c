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
struct TYPE_3__ {char const* zDefaultDb; int /*<<< orphan*/  zName; } ;

/* Variables and functions */
 int ArraySize (TYPE_1__*) ; 
 TYPE_1__* aLib ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

const char *tdb_default_db(const char *zSys){
  int i;
  for(i=0; i<ArraySize(aLib); i++){
    if( strcmp(aLib[i].zName, zSys)==0 ) return aLib[i].zDefaultDb;
  }
  return 0;
}