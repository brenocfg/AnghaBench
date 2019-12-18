#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* buf; char* len; } ;
struct TYPE_5__ {scalar_t__ nCallingConvention; int uFlags; int nNumber; int nArgCount; int* anArgs; TYPE_1__ strName; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ EXPORT ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
#define  ARG_DBL 135 
#define  ARG_FLOAT 134 
#define  ARG_INT128 133 
#define  ARG_INT64 132 
#define  ARG_LONG 131 
#define  ARG_PTR 130 
#define  ARG_STR 129 
#define  ARG_WSTR 128 
 scalar_t__ CC_STDCALL ; 
 scalar_t__ CC_STUB ; 
 int FL_NORELAY ; 
 int FL_REGISTER ; 
 int FL_RET64 ; 
 int FL_STUB ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gbTracing ; 
 scalar_t__ giArch ; 
 char* pszDllName ; 

int
OutputLine_stub(FILE *file, EXPORT *pexp)
{
    int i;
    int bRelay = 0;
    int bInPrototype = 0;

    if (pexp->nCallingConvention != CC_STUB &&
        (pexp->uFlags & FL_STUB) == 0)
    {
        /* Only relay trace stdcall C functions */
        if (!gbTracing || (pexp->nCallingConvention != CC_STDCALL)
                || (pexp->uFlags & FL_NORELAY)
                || (pexp->strName.buf[0] == '?'))
        {
            return 0;
        }
        bRelay = 1;
    }

    /* Declare the "real" function */
    if (bRelay)
    {
        fprintf(file, "extern ");
        bInPrototype = 1;
    }

    do
    {
        if (pexp->uFlags & FL_REGISTER)
        {
            /* FIXME: Not sure this is right */
            fprintf(file, "void ");
        }
        else if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "__int64 ");
        }
        else
        {
            fprintf(file, "int ");
        }

        if ((giArch == ARCH_X86) &&
            pexp->nCallingConvention == CC_STDCALL)
        {
            fprintf(file, "__stdcall ");
        }

        /* Check for C++ */
        if (pexp->strName.buf[0] == '?')
        {
            fprintf(file, "stub_function%d(", pexp->nNumber);
        }
        else
        {
            if (!bRelay || bInPrototype)
                fprintf(file, "%.*s(", pexp->strName.len, pexp->strName.buf);
            else
                fprintf(file, "$relaytrace$%.*s(", pexp->strName.len, pexp->strName.buf);
        }

        for (i = 0; i < pexp->nArgCount; i++)
        {
            if (i != 0) fprintf(file, ", ");
            switch (pexp->anArgs[i])
            {
                case ARG_LONG: fprintf(file, "long"); break;
                case ARG_PTR:  fprintf(file, "void*"); break;
                case ARG_STR:  fprintf(file, "char*"); break;
                case ARG_WSTR: fprintf(file, "wchar_t*"); break;
                case ARG_DBL:  fprintf(file, "double"); break;
                case ARG_INT64 :  fprintf(file, "__int64"); break;
                /* __int128 is not supported on x86, and int128 in spec files most often represents a GUID */
                case ARG_INT128 :  fprintf(file, "GUID"); break;
                case ARG_FLOAT: fprintf(file, "float"); break;
            }
            fprintf(file, " a%d", i);
        }

        if (bInPrototype)
        {
            fprintf(file, ");\n\n");
        }
    } while (bInPrototype--);

    if (!bRelay)
    {
        fprintf(file, ")\n{\n\tDbgPrint(\"WARNING: calling stub %.*s(",
                pexp->strName.len, pexp->strName.buf);
    }
    else
    {
        fprintf(file, ")\n{\n");
        if (pexp->uFlags & FL_REGISTER)
        {
            /* No return value */
        }
        else if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "\t__int64 retval;\n");
        }
        else
        {
            fprintf(file, "\tint retval;\n");
        }
        fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s(",
                pszDllName, pexp->strName.len, pexp->strName.buf);
    }

    for (i = 0; i < pexp->nArgCount; i++)
    {
        if (i != 0) fprintf(file, ",");
        switch (pexp->anArgs[i])
        {
            case ARG_LONG: fprintf(file, "0x%%lx"); break;
            case ARG_PTR:  fprintf(file, "0x%%p"); break;
            case ARG_STR:  fprintf(file, "'%%s'"); break;
            case ARG_WSTR: fprintf(file, "'%%ws'"); break;
            case ARG_DBL:  fprintf(file, "%%f"); break;
            case ARG_INT64: fprintf(file, "%%\"PRIx64\""); break;
            case ARG_INT128: fprintf(file, "'%%s'"); break;
            case ARG_FLOAT: fprintf(file, "%%f"); break;
        }
    }
    fprintf(file, ")\\n\"");

    for (i = 0; i < pexp->nArgCount; i++)
    {
        fprintf(file, ", ");
        switch (pexp->anArgs[i])
        {
            case ARG_LONG: fprintf(file, "(long)a%d", i); break;
            case ARG_PTR:  fprintf(file, "(void*)a%d", i); break;
            case ARG_STR:  fprintf(file, "(char*)a%d", i); break;
            case ARG_WSTR: fprintf(file, "(wchar_t*)a%d", i); break;
            case ARG_DBL:  fprintf(file, "(double)a%d", i); break;
            case ARG_INT64: fprintf(file, "(__int64)a%d", i); break;
            case ARG_INT128: fprintf(file, "wine_dbgstr_guid(&a%d)", i); break;
            case ARG_FLOAT: fprintf(file, "(float)a%d", i); break;
        }
    }
    fprintf(file, ");\n");

    if (pexp->nCallingConvention == CC_STUB)
    {
        fprintf(file, "\t__wine_spec_unimplemented_stub(\"%s\", __FUNCTION__);\n", pszDllName);
    }
    else if (bRelay)
    {
        if (pexp->uFlags & FL_REGISTER)
        {
            fprintf(file,"\t");
        }
        else
        {
            fprintf(file, "\tretval = ");
        }
        fprintf(file, "%.*s(", pexp->strName.len, pexp->strName.buf);

        for (i = 0; i < pexp->nArgCount; i++)
        {
            if (i != 0) fprintf(file, ", ");
            fprintf(file, "a%d", i);
        }
        fprintf(file, ");\n");
    }

    if (!bRelay)
        fprintf(file, "\treturn 0;\n}\n\n");
    else if ((pexp->uFlags & FL_REGISTER) == 0)
    {
        if (pexp->uFlags & FL_RET64)
        {
            fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s: retval = %%\"PRIx64\"\\n\", retval);\n",
                    pszDllName, pexp->strName.len, pexp->strName.buf);
        }
        else
        {
            fprintf(file, "\tif (TRACE_ON(relay))\n\t\tDPRINTF(\"%s: %.*s: retval = 0x%%lx\\n\", retval);\n",
                    pszDllName, pexp->strName.len, pexp->strName.buf);
        }
        fprintf(file, "\treturn retval;\n}\n\n");
    }

    return 1;
}