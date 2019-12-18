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

/* Variables and functions */
 unsigned int MAX_NUMBER ; 
 int* bson_numstr_len ; 
 int /*<<< orphan*/ * bson_numstrs ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static inline int 
bson_numstr( char *str, unsigned int i ) {
	if ( i < MAX_NUMBER) {
		memcpy( str, bson_numstrs[i], 4 );
		return bson_numstr_len[i];
	} else {
		return sprintf( str,"%u", i );
	}
}