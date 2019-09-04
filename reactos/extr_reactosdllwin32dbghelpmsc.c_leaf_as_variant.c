#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short uintVal; char cVal; short iVal; unsigned short uiVal; int lVal; long long llVal; unsigned long long ullVal; float fltVal; } ;
struct TYPE_7__ {void* vt; TYPE_1__ n3; } ;
struct TYPE_8__ {TYPE_2__ n2; } ;
struct TYPE_9__ {TYPE_3__ n1; } ;
typedef  TYPE_4__ VARIANT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,unsigned short) ; 
#define  LF_CHAR 144 
#define  LF_COMPLEX128 143 
#define  LF_COMPLEX32 142 
#define  LF_COMPLEX64 141 
#define  LF_COMPLEX80 140 
#define  LF_LONG 139 
 unsigned short LF_NUMERIC ; 
#define  LF_QUADWORD 138 
#define  LF_REAL128 137 
#define  LF_REAL32 136 
#define  LF_REAL48 135 
#define  LF_REAL64 134 
#define  LF_REAL80 133 
#define  LF_SHORT 132 
#define  LF_ULONG 131 
#define  LF_UQUADWORD 130 
#define  LF_USHORT 129 
#define  LF_VARSTRING 128 
 void* VT_EMPTY ; 
 void* VT_I1 ; 
 void* VT_I2 ; 
 void* VT_I4 ; 
 void* VT_I8 ; 
 void* VT_R4 ; 
 void* VT_R8 ; 
 void* VT_UI2 ; 
 void* VT_UI4 ; 
 void* VT_UI8 ; 
 void* VT_UINT ; 

__attribute__((used)) static int leaf_as_variant(VARIANT* v, const unsigned short int* leaf)
{
    unsigned short int type = *leaf++;
    int length = 2;

    if (type < LF_NUMERIC)
    {
        v->n1.n2.vt = VT_UINT;
        v->n1.n2.n3.uintVal = type;
    }
    else
    {
        switch (type)
        {
        case LF_CHAR:
            length += 1;
            v->n1.n2.vt = VT_I1;
            v->n1.n2.n3.cVal = *(const char*)leaf;
            break;

        case LF_SHORT:
            length += 2;
            v->n1.n2.vt = VT_I2;
            v->n1.n2.n3.iVal = *(const short*)leaf;
            break;

        case LF_USHORT:
            length += 2;
            v->n1.n2.vt = VT_UI2;
            v->n1.n2.n3.uiVal = *leaf;
            break;

        case LF_LONG:
            length += 4;
            v->n1.n2.vt = VT_I4;
            v->n1.n2.n3.lVal = *(const int*)leaf;
            break;

        case LF_ULONG:
            length += 4;
            v->n1.n2.vt = VT_UI4;
            v->n1.n2.n3.uiVal = *(const unsigned int*)leaf;
            break;

        case LF_QUADWORD:
            length += 8;
            v->n1.n2.vt = VT_I8;
            v->n1.n2.n3.llVal = *(const long long int*)leaf;
            break;

        case LF_UQUADWORD:
            length += 8;
            v->n1.n2.vt = VT_UI8;
            v->n1.n2.n3.ullVal = *(const long long unsigned int*)leaf;
            break;

        case LF_REAL32:
            length += 4;
            v->n1.n2.vt = VT_R4;
            v->n1.n2.n3.fltVal = *(const float*)leaf;
            break;

        case LF_REAL48:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 6;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_REAL64:
            length += 8;
            v->n1.n2.vt = VT_R8;
            v->n1.n2.n3.fltVal = *(const double*)leaf;
            break;

        case LF_REAL80:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 10;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_REAL128:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 16;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_COMPLEX32:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 4;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_COMPLEX64:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 8;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_COMPLEX80:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 10;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_COMPLEX128:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 16;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        case LF_VARSTRING:
	    FIXME("Unsupported numeric leaf type %04x\n", type);
            length += 2 + *leaf;
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;

        default:
	    FIXME("Unknown numeric leaf type %04x\n", type);
            v->n1.n2.vt = VT_EMPTY;     /* FIXME */
            break;
        }
    }

    return length;
}