/*
	Shaun's optimization
*/

#ifndef OPTIMIZATION_SHAUN
#define OPTMIZATION_SHAUN

#define BZ_THREADSAFE 

//循环展开1
//#define LOOP_UNROLL

//循环展开2
//#define ANTIALIAS

//SIMD向量化1
#define VECTOR_ALIGN

//SIMD向量化2
//#define VECTOR_ALIGN1

//使用RESTRICT关键字
//#define RESTRICT

//使用chrono库计时，而不是rdtsc
//#define CHRONO

//AVX2指令集的位宽
#define VECTORIZED_LOOP_WIDTH 32

//开启OMP优化
//#define OMP

#include <chrono>

//使用chrono计时的宏
#define TIMERSTART(tag)  auto tag##_start = std::chrono::steady_clock::now(),tag##_end = tag##_start
#define TIMEREND(tag)  tag##_end =  std::chrono::steady_clock::now()
#define DURATION_s(tag) printf("%s costs %d s\n",#tag,std::chrono::duration_cast<std::chrono::seconds>(tag##_end - tag##_start).count())
#define DURATION_ms(tag) printf("%s costs %d ms\n",#tag,std::chrono::duration_cast<std::chrono::milliseconds>(tag##_end - tag##_start).count());
#define DURATION_us(tag) printf("%s costs %d us\n",#tag,std::chrono::duration_cast<std::chrono::microseconds>(tag##_end - tag##_start).count());
#define DURATION_ns(tag) printf("%s costs %d ns\n",#tag,std::chrono::duration_cast<std::chrono::nanoseconds>(tag##_end - tag##_start).count());

  template<typename T_numtype, typename T_expr, typename T_update>
  void
  evaluate_aligned(T_numtype* data, T_expr &expr, T_update) {
#pragma ivdep
#pragma vector aligned
	  for (int i = 0; i < VECTORIZED_LOOP_WIDTH; ++i)
			  T_update::update(data[i], expr.fastRead(i));
  }


#ifdef _WIN32
#include <windows.h>
#else
#include <sys/sysinfo.h>
#endif

//获取CPU核心数，其实这里可以直接使用openmp的函数omp_get_num_procs()
int get_cpu_cores()
{
#ifdef _WIN32
    SYSTEM_INFO info;
    GetSystemInfo (&info);
    return info.dwNumberOfProcessors;
#else
    return get_nprocs();   //GNU fuction
#endif
}

#endif