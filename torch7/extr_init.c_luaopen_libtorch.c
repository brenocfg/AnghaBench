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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaT_newmetatable (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  torch_ByteStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_ByteTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_ByteTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_CharStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_CharTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_CharTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_DiskFile_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_DoubleStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_DoubleTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_DoubleTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_File_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_FloatStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_FloatTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_FloatTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_HalfStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_HalfTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_IntStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_IntTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_IntTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_LongStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_LongTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_LongTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_MemoryFile_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_PipeFile_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_ShortStorage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_ShortTensorOperator_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_ShortTensor_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_TensorMath_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_Timer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_random_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torch_utils_init (int /*<<< orphan*/ *) ; 

int luaopen_libtorch(lua_State *L)
{

  lua_newtable(L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, "torch");

  torch_utils_init(L);
  torch_File_init(L);

  torch_ByteStorage_init(L);
  torch_CharStorage_init(L);
  torch_ShortStorage_init(L);
  torch_IntStorage_init(L);
  torch_LongStorage_init(L);
  torch_FloatStorage_init(L);
  torch_DoubleStorage_init(L);
  torch_HalfStorage_init(L);

  torch_ByteTensor_init(L);
  torch_CharTensor_init(L);
  torch_ShortTensor_init(L);
  torch_IntTensor_init(L);
  torch_LongTensor_init(L);
  torch_FloatTensor_init(L);
  torch_DoubleTensor_init(L);
  torch_HalfTensor_init(L);

  torch_ByteTensorOperator_init(L);
  torch_CharTensorOperator_init(L);
  torch_ShortTensorOperator_init(L);
  torch_IntTensorOperator_init(L);
  torch_LongTensorOperator_init(L);
  torch_FloatTensorOperator_init(L);
  torch_DoubleTensorOperator_init(L);

  torch_Timer_init(L);
  torch_DiskFile_init(L);
  torch_PipeFile_init(L);
  torch_MemoryFile_init(L);

  torch_TensorMath_init(L);

  torch_random_init(L);

  // Create 'torch.Allocator' type.
  luaT_newmetatable(L, "torch.Allocator", NULL, NULL, NULL, NULL);

  return 1;
}