// 1D Matrix Addition

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL\cl.h>
#endif

int main()
{
	unsigned int i, j;
	int queryInt;
	cl_ulong queryLInt;
	cl_device_fp_config queryFP;
	cl_device_exec_capabilities queryEX;
	cl_device_mem_cache_type queryCH;
	cl_command_queue_properties queryQU;
	cl_device_type queryTY;
	size_t size;
	cl_bool flag = CL_FALSE;
	char queryBuffer[1024];

	//Get platform and device information
	cl_platform_id* platforms = NULL;
	cl_uint num_platforms;

	//Set up the platform
	cl_int clStatus = clGetPlatformIDs(0, NULL, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
	clStatus = clGetPlatformIDs(num_platforms, platforms, NULL);

	//Get the platforms information
	printf("\n	==========================================PLATFORM_INFORMATION================================	\n\n");
	for (i = 0; i <num_platforms; i++)
	{
		clStatus = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(queryBuffer), &queryBuffer, NULL);
		printf("CL_PLATFORM_NAME %d	:	%s	\n", i, queryBuffer);
		queryBuffer[0] = '\0';
		clStatus = clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(queryBuffer), &queryBuffer, NULL);
		printf("CL_PLATFORM_VENDOR %d	:	%s	\n", i, queryBuffer);
		queryBuffer[0] = '\0';
		clStatus = clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, sizeof(queryBuffer), &queryBuffer, NULL);
		printf("CL_PLATFORM_VERSION %d	:	%s	\n", i, queryBuffer);
		queryBuffer[0] = '\0';
		clStatus = clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, sizeof(queryBuffer), &queryBuffer, NULL);
		printf("CL_PLATFORM_PROFILE %d	:	%s	\n", i, queryBuffer);
		queryBuffer[0] = '\0';
		clStatus = clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, sizeof(queryBuffer), &queryBuffer, NULL);
		printf("CL_PLATFORM_EXTENSION %d	:	%s \n", i, queryBuffer);
		queryBuffer[0] = '\0';

	}

	//Get the devices list and choose the device you want to run on
	cl_device_id* device_list = NULL;
	cl_uint num_devices;
	for (i = 0; i < num_platforms; i++)
	{
		clStatus = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
		device_list = (cl_device_id*)malloc(sizeof(cl_device_id)*num_devices);
		clStatus = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, device_list, NULL);

		//Display all device information in corresponding platforms
		printf("\n	==========================================DEVICE_INFORMATION================================	\n\n");
		for (j = 0; j < num_devices; j++)
		{
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_NAME, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DEVICE_NAME	%d	:	%s	\n", j, queryBuffer);
			queryBuffer[0] = '\0';
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_VENDOR, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DEVICE_VENDOR	%d	:	%s	\n", j, queryBuffer);
			queryBuffer[0] = '\0';
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_VENDOR_ID, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_VENDOR_ID	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_VERSION, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DEVICE_VERSION	%d	:	%s	\n", j, queryBuffer);
			queryBuffer[0] = '\0';
			clStatus = clGetDeviceInfo(device_list[j], CL_DRIVER_VERSION, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DRIVER_VERSION	%d	:	%s	\n", j, queryBuffer);
			queryBuffer[0] = '\0';
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_COMPUTE_UNITS %d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_ADDRESS_BITS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_ADDRESS_BITS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_AVAILABLE, sizeof(flag), &flag, NULL);
			printf("CL_DEVICE_AVAILABLE	%d	:	%d	\n", j, flag);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_COMPILER_AVAILABLE, sizeof(flag), &flag, NULL);
			printf("CL_DEVICE_COMPILER_AVAILABLE	%d	:	%d	\n", j, flag);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_ENDIAN_LITTLE, sizeof(flag), &flag, NULL);
			printf("CL_DEVICE_ENDIAN_LITTLE	%d	:	%d	\n", j, flag);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_ERROR_CORRECTION_SUPPORT, sizeof(flag), &flag, NULL);
			printf("CL_DEVICE_ERROR_CORRECTION_SUPPORT	%d	:	%d	\n", j, flag);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_EXTENSIONS, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DEVICE_EXTENSIONS	%d	:	%s \n", j, queryBuffer);
			queryBuffer[0] = '\0';
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(queryLInt), &queryLInt, NULL);
			printf("CL_DEVICE_GLOBAL_MEM_CACHE_SIZE	%d	:	%u	\n", j, queryLInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(queryLInt), &queryLInt, NULL);
			printf("CL_DEVICE_GLOBAL_MEM_SIZE	%d	:	%u	\n", j, queryLInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE_SUPPORT, sizeof(flag), &flag, NULL);
			printf("CL_DEVICE_IMAGE_SUPPORT	%d	:	%d	\n", j, flag);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(size), &size, NULL);
			printf("CL_DEVICE_IMAGE2D_MAX_HEIGHT	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(size), &size, NULL);
			printf("CL_DEVICE_IMAGE2D_MAX_WIDTH	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE3D_MAX_DEPTH, sizeof(size), &size, NULL);
			printf("CL_DEVICE_IMAGE3D_MAX_DEPTH	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE3D_MAX_WIDTH, sizeof(size), &size, NULL);
			printf("CL_DEVICE_IMAGE3D_MAX_WIDTH	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_IMAGE3D_MAX_HEIGHT, sizeof(size), &size, NULL);
			printf("CL_DEVICE_IMAGE3D_MAX_HEIGHT	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(queryLInt), &queryLInt, NULL);
			printf("CL_DEVICE_LOCAL_MEM_SIZE	%d	:	%u	\n", j, queryLInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_CLOCK_FREQUENCY	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_CONSTANT_ARGS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(queryLInt), &queryLInt, NULL);
			printf("CL_DEVICE_MAX_CONSTATNT_BUFFER_SIZE	%d	:	%u	\n", j, queryLInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(queryLInt), &queryLInt, NULL);
			printf("CL_DEVICE_MAX_MEM_ALLOC_SIZE	%d	:	%u	\n", j, queryLInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_PARAMETER_SIZE, sizeof(size), &size, NULL);
			printf("CL_DEVICE_MAX_PARAMETER_SIZE	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_READ_IMAGE_ARGS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_SAMPLERS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_SAMPLERS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size), &size, NULL);
			printf("CL_DEVICE_MAX_WORK_GROUP_SIZE	%d	:	 %u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_ITEM_DIMENSIONS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size), &size, NULL);
			printf("CL_DEVICE_MAX_WORK_ITEM_SIZES	%d	:	%u	\n", j, size);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MAX_WRITE_IMAGE_ARGS	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_MEM_BASE_ADDR_ALIGN, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_MEM_BASE_ADDR_ALIGN	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTORE_WIDTH_FLOAT	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(queryInt), &queryInt, NULL);
			printf("CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE	%d	:	%d	\n", j, queryInt);
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_PROFILE, sizeof(queryBuffer), &queryBuffer, NULL);
			printf("CL_DEVICE_PROFILE	%d	:	%s	\n", j, queryBuffer);
			queryBuffer[0] = '\0';
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_DOUBLE_FP_CONFIG++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(queryFP), &queryFP, NULL);
			(queryFP & CL_FP_DENORM) ? printf("CL_FP_DENORM	%d	:	TRUE	\n", j) : printf("CL_FP_DENORM	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_INF_NAN) ? printf("CL_FP_INF_NAN	%d	:	TRUE	\n", j) : printf("CL_FP_INF_NAN	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_NEAREST) ? printf("CL_FP_ROUND_TO_NEAREST	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_NEAREST	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_ZERO) ? printf("CL_FP_ROUND_TO_ZERO	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_ZERO %d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_INF) ? printf("CL_FP_ROUND_TO_INF	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_INF	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_FMA) ? printf("CL_FP_FMA	%d	:	TRUE	\n", j) : printf("CL_FP_FMA	%d	:	FALSE	\n", j);
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_SINGLE_FP_CONFIG++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_SINGLE_FP_CONFIG, sizeof(queryFP), &queryFP, NULL);
			(queryFP & CL_FP_DENORM) ? printf("CL_FP_DENORM	%d	:	TRUE	\n", j) : printf("CL_FP_DENORM	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_INF_NAN) ? printf("CL_FP_INF_NAN	%d	:	TRUE	\n", j) : printf("CL_FP_INF_NAN	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_NEAREST) ? printf("CL_FP_ROUND_TO_NEAREST	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_NEAREST	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_ZERO) ? printf("CL_FP_ROUND_TO_ZERO	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_ZERO %d	:	FALSE	\n", j);
			(queryFP & CL_FP_ROUND_TO_INF) ? printf("CL_FP_ROUND_TO_INF	%d	:	TRUE	\n", j) : printf("CL_FP_ROUND_TO_INF	%d	:	FALSE	\n", j);
			(queryFP & CL_FP_FMA) ? printf("CL_FP_FMA	%d	:	TRUE	\n", j) : printf("CL_FP_FMA	%d	:	FALSE	\n", j);
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_EXECUTION_CAPABILITIES++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_EXECUTION_CAPABILITIES, sizeof(queryEX), &queryEX, NULL);
			(queryEX & CL_EXEC_KERNEL) ? printf("CL_EXEC_KERNEL	%d	:	TRUE	\n", j) : printf("CL_EXEC_KERNEL	%d	:	FALSE	\n", j);
			(queryEX & CL_EXEC_NATIVE_KERNEL) ? printf("CL_EXEC_NATIVE_KERNEL	%d	:	TRUE	\n", j) : printf("CL_EXEC_NATIVE_KERNEL	%d	:	FALSE	\n", j);
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_GLOBAL_MEM_CACHE_TYPE++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, sizeof(queryCH), &queryCH, NULL);
			(queryCH & CL_NONE) ? printf("CL_NONE	%d	:	NO CACHE	\n", j) : ((queryCH & CL_READ_ONLY_CACHE) ? printf("CL_READ_ONLY_CACHE %d	:	TRUE	\n", j) : printf("CL_READ_WRITE_CACHE	%d	:	TRUE	\n", j));
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_QUEUE_PROPERTIES++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_QUEUE_PROPERTIES, sizeof(queryQU), &queryQU, NULL);
			(queryCH & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) ? printf("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE	%d	:	TRUE	\n", j) : printf("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE	%d	:	FALSE	\n", j);
			(queryCH & CL_QUEUE_PROFILING_ENABLE) ? printf("CL_QUEUE_PROFILING_ENABLE	%d	:	TRUE	\n", j) : printf("CL_QUEUE_PROFILING_ENABLE %d	:	FALSE	\n", j);
			printf("\n	+++++++++++++++++++++++++++++++++++++CL_DEVICE_TYPE++++++++++++++++++++++++++++	\n\n");
			clStatus = clGetDeviceInfo(device_list[j], CL_DEVICE_TYPE, sizeof(queryTY), &queryTY, NULL);
			(queryTY & CL_DEVICE_TYPE_CPU) ? printf("CL_DEVICE_TYPE_CPU	%d	:	TRUE	\n", j) : printf("CL_DEVICE_TYPE_CPU	%d	:	FALSE	\n", j);
			(queryTY & CL_DEVICE_TYPE_GPU) ? printf("CL_DEVICE_TYPE_GPU	%d	:	TRUE	\n", j) : printf("CL_DEVICE_TYPE_GPU	%d	:	FALSE	\n", j);
			(queryTY & CL_DEVICE_TYPE_ACCELERATOR) ? printf("CL_DEVICE_TYPE_ACCELERATOR	%d	:	TRUE \n", j) : printf("CL_DEVICE_TYPE_ACCELERATOR	%d	:	FALSE	\n", j);
			(queryTY & CL_DEVICE_TYPE_DEFAULT) ? printf("CL_DEVICE_TYPE_DEFAULT	%d	:	TRUE	\n", j) : printf("CL_DEVICE_TYPE_DEFAULT	%d	:	FALSE	\n", j);
		}
	}
	getchar();
}
