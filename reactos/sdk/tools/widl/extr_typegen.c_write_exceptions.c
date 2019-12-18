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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void write_exceptions( FILE *file )
{
    fprintf( file, "#ifndef USE_COMPILER_EXCEPTIONS\n");
    fprintf( file, "\n");
    fprintf( file, "#include \"wine/exception.h\"\n");
    fprintf( file, "#undef RpcTryExcept\n");
    fprintf( file, "#undef RpcExcept\n");
    fprintf( file, "#undef RpcEndExcept\n");
    fprintf( file, "#undef RpcTryFinally\n");
    fprintf( file, "#undef RpcFinally\n");
    fprintf( file, "#undef RpcEndFinally\n");
    fprintf( file, "#undef RpcExceptionCode\n");
    fprintf( file, "#undef RpcAbnormalTermination\n");
    fprintf( file, "\n");
    fprintf( file, "struct __exception_frame;\n");
    fprintf( file, "typedef int (*__filter_func)(struct __exception_frame *);\n");
    fprintf( file, "typedef void (*__finally_func)(struct __exception_frame *);\n");
    fprintf( file, "\n");
    fprintf( file, "#define __DECL_EXCEPTION_FRAME \\\n");
    fprintf( file, "    EXCEPTION_REGISTRATION_RECORD frame; \\\n");
    fprintf( file, "    __filter_func                 filter; \\\n");
    fprintf( file, "    __finally_func                finally; \\\n");
    fprintf( file, "    sigjmp_buf                    jmp; \\\n");
    fprintf( file, "    DWORD                         code; \\\n");
    fprintf( file, "    unsigned char                 abnormal_termination; \\\n");
    fprintf( file, "    unsigned char                 filter_level; \\\n");
    fprintf( file, "    unsigned char                 finally_level;\n");
    fprintf( file, "\n");
    fprintf( file, "struct __exception_frame\n{\n");
    fprintf( file, "    __DECL_EXCEPTION_FRAME\n");
    fprintf( file, "};\n");
    fprintf( file, "\n");
    fprintf( file, "static inline void __widl_unwind_target(void)\n" );
    fprintf( file, "{\n");
    fprintf( file, "    struct __exception_frame *exc_frame = (struct __exception_frame *)__wine_get_frame();\n" );
    fprintf( file, "    if (exc_frame->finally_level > exc_frame->filter_level)\n" );
    fprintf( file, "    {\n");
    fprintf( file, "        exc_frame->abnormal_termination = 1;\n");
    fprintf( file, "        exc_frame->finally( exc_frame );\n");
    fprintf( file, "        __wine_pop_frame( &exc_frame->frame );\n");
    fprintf( file, "    }\n");
    fprintf( file, "    exc_frame->filter_level = 0;\n");
    fprintf( file, "    siglongjmp( exc_frame->jmp, 1 );\n");
    fprintf( file, "}\n");
    fprintf( file, "\n");
    fprintf( file, "static DWORD __widl_exception_handler( EXCEPTION_RECORD *record,\n");
    fprintf( file, "                                       EXCEPTION_REGISTRATION_RECORD *frame,\n");
    fprintf( file, "                                       CONTEXT *context,\n");
    fprintf( file, "                                       EXCEPTION_REGISTRATION_RECORD **pdispatcher )\n");
    fprintf( file, "{\n");
    fprintf( file, "    struct __exception_frame *exc_frame = (struct __exception_frame *)frame;\n");
    fprintf( file, "\n");
    fprintf( file, "    if (record->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND | EH_NESTED_CALL))\n");
    fprintf( file, "    {\n" );
    fprintf( file, "        if (exc_frame->finally_level && (record->ExceptionFlags & (EH_UNWINDING | EH_EXIT_UNWIND)))\n");
    fprintf( file, "        {\n" );
    fprintf( file, "            exc_frame->abnormal_termination = 1;\n");
    fprintf( file, "            exc_frame->finally( exc_frame );\n");
    fprintf( file, "        }\n" );
    fprintf( file, "        return ExceptionContinueSearch;\n");
    fprintf( file, "    }\n" );
    fprintf( file, "    exc_frame->code = record->ExceptionCode;\n");
    fprintf( file, "    if (exc_frame->filter_level && exc_frame->filter( exc_frame ) == EXCEPTION_EXECUTE_HANDLER)\n" );
    fprintf( file, "        __wine_rtl_unwind( frame, record, __widl_unwind_target );\n");
    fprintf( file, "    return ExceptionContinueSearch;\n");
    fprintf( file, "}\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcTryExcept \\\n");
    fprintf( file, "    if (!sigsetjmp( __frame->jmp, 0 )) \\\n");
    fprintf( file, "    { \\\n");
    fprintf( file, "        if (!__frame->finally_level) \\\n" );
    fprintf( file, "            __wine_push_frame( &__frame->frame ); \\\n");
    fprintf( file, "        __frame->filter_level = __frame->finally_level + 1;\n" );
    fprintf( file, "\n");
    fprintf( file, "#define RpcExcept(expr) \\\n");
    fprintf( file, "        if (!__frame->finally_level) \\\n" );
    fprintf( file, "            __wine_pop_frame( &__frame->frame ); \\\n");
    fprintf( file, "        __frame->filter_level = 0; \\\n" );
    fprintf( file, "    } \\\n");
    fprintf( file, "    else \\\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcEndExcept\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcExceptionCode() (__frame->code)\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcTryFinally \\\n");
    fprintf( file, "    if (!__frame->filter_level) \\\n");
    fprintf( file, "        __wine_push_frame( &__frame->frame ); \\\n");
    fprintf( file, "    __frame->finally_level = __frame->filter_level + 1;\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcFinally \\\n");
    fprintf( file, "    if (!__frame->filter_level) \\\n");
    fprintf( file, "        __wine_pop_frame( &__frame->frame ); \\\n");
    fprintf( file, "    __frame->finally_level = 0;\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcEndFinally\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcAbnormalTermination() (__frame->abnormal_termination)\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcExceptionInit(filter_func,finally_func) \\\n");
    fprintf( file, "    do { \\\n");
    fprintf( file, "        __frame->frame.Handler = __widl_exception_handler; \\\n");
    fprintf( file, "        __frame->filter = (__filter_func)(filter_func); \\\n" );
    fprintf( file, "        __frame->finally = (__finally_func)(finally_func); \\\n");
    fprintf( file, "        __frame->abnormal_termination = 0; \\\n");
    fprintf( file, "        __frame->filter_level = 0; \\\n");
    fprintf( file, "        __frame->finally_level = 0; \\\n");
    fprintf( file, "    } while (0)\n");
    fprintf( file, "\n");
    fprintf( file, "#else /* USE_COMPILER_EXCEPTIONS */\n");
    fprintf( file, "\n");
    fprintf( file, "#define RpcExceptionInit(filter_func,finally_func) \\\n");
    fprintf( file, "    do { (void)(filter_func); } while(0)\n");
    fprintf( file, "\n");
    fprintf( file, "#define __DECL_EXCEPTION_FRAME \\\n");
    fprintf( file, "    DWORD code;\n");
    fprintf( file, "\n");
    fprintf( file, "#endif /* USE_COMPILER_EXCEPTIONS */\n");
}