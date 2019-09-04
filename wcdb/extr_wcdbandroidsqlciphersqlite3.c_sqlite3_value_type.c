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
typedef  int u8 ;
struct TYPE_3__ {size_t flags; } ;
typedef  TYPE_1__ sqlite3_value ;

/* Variables and functions */
 size_t MEM_AffMask ; 
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 

int sqlite3_value_type(sqlite3_value* pVal){
  static const u8 aType[] = {
     SQLITE_BLOB,     /* 0x00 */
     SQLITE_NULL,     /* 0x01 */
     SQLITE_TEXT,     /* 0x02 */
     SQLITE_NULL,     /* 0x03 */
     SQLITE_INTEGER,  /* 0x04 */
     SQLITE_NULL,     /* 0x05 */
     SQLITE_INTEGER,  /* 0x06 */
     SQLITE_NULL,     /* 0x07 */
     SQLITE_FLOAT,    /* 0x08 */
     SQLITE_NULL,     /* 0x09 */
     SQLITE_FLOAT,    /* 0x0a */
     SQLITE_NULL,     /* 0x0b */
     SQLITE_INTEGER,  /* 0x0c */
     SQLITE_NULL,     /* 0x0d */
     SQLITE_INTEGER,  /* 0x0e */
     SQLITE_NULL,     /* 0x0f */
     SQLITE_BLOB,     /* 0x10 */
     SQLITE_NULL,     /* 0x11 */
     SQLITE_TEXT,     /* 0x12 */
     SQLITE_NULL,     /* 0x13 */
     SQLITE_INTEGER,  /* 0x14 */
     SQLITE_NULL,     /* 0x15 */
     SQLITE_INTEGER,  /* 0x16 */
     SQLITE_NULL,     /* 0x17 */
     SQLITE_FLOAT,    /* 0x18 */
     SQLITE_NULL,     /* 0x19 */
     SQLITE_FLOAT,    /* 0x1a */
     SQLITE_NULL,     /* 0x1b */
     SQLITE_INTEGER,  /* 0x1c */
     SQLITE_NULL,     /* 0x1d */
     SQLITE_INTEGER,  /* 0x1e */
     SQLITE_NULL,     /* 0x1f */
  };
  return aType[pVal->flags&MEM_AffMask];
}