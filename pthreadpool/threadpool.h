#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "array_queue.h"
typedef struct ThreadPool
{
	pthread_t* tid;
	size_t thread_cnt;
	void (*task)(void*);
	ArrayQueue* queue;
	pthread_mutex_t mutex;
	pthread_cond_t full;
	pthread_cond_t null;
}ThreadPool;

// 创建线程池
ThreadPool* tp_create(size_t cnt,size_t cal,void (*task)(void*));

// 销毁线程池
void tp_destory(ThreadPool* tp);

// 启动
void start(ThreadPool* tp);

// 生产
void tp_push(ThreadPool* tp,void* ptr);

// 消费
void* tp_pop(ThreadPool* tp);

#endif//THREADPOOL_H
