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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* cuGetErrorString ) (scalar_t__,char const**) ;int /*<<< orphan*/  (* cuGetErrorName ) (scalar_t__,char const**) ;} ;
typedef  TYPE_1__ CudaFunctions ;
typedef  scalar_t__ CUresult ;

/* Variables and functions */
 scalar_t__ CUDA_SUCCESS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char const**) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,char const**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int CudaCheckErr(vlc_object_t *obj, CudaFunctions *cudaFunctions, CUresult result, const char *psz_func)
{
    if (unlikely(result != CUDA_SUCCESS)) {
        const char *psz_err, *psz_err_str;
        cudaFunctions->cuGetErrorName(result, &psz_err);
        cudaFunctions->cuGetErrorString(result, &psz_err_str);
        msg_Err(obj, "%s failed: %s (%s)", psz_func, psz_err_str, psz_err);
        return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}