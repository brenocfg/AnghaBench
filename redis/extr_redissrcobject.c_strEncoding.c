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
#define  OBJ_ENCODING_EMBSTR 135 
#define  OBJ_ENCODING_HT 134 
#define  OBJ_ENCODING_INT 133 
#define  OBJ_ENCODING_INTSET 132 
#define  OBJ_ENCODING_QUICKLIST 131 
#define  OBJ_ENCODING_RAW 130 
#define  OBJ_ENCODING_SKIPLIST 129 
#define  OBJ_ENCODING_ZIPLIST 128 

char *strEncoding(int encoding) {
    switch(encoding) {
    case OBJ_ENCODING_RAW: return "raw";
    case OBJ_ENCODING_INT: return "int";
    case OBJ_ENCODING_HT: return "hashtable";
    case OBJ_ENCODING_QUICKLIST: return "quicklist";
    case OBJ_ENCODING_ZIPLIST: return "ziplist";
    case OBJ_ENCODING_INTSET: return "intset";
    case OBJ_ENCODING_SKIPLIST: return "skiplist";
    case OBJ_ENCODING_EMBSTR: return "embstr";
    default: return "unknown";
    }
}