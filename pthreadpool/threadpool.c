#include <stdlib.h>
#include <pthread.h>
#include "threadpool.h"

// 创建线程池
ThreadPool* tp_create(size_t cnt,size_t cal,void (*task)(void*))
{
	ThreadPool* tp = malloc(sizeof(ThreadPool));
	tp->thread_cnt = cnt;
	tp->queue = create_queue(cal);
	tp->tid = malloc(sizeof(pthread_t)*cnt);
	tp->task = task;
	pthread_mutex_init(&tp->mutex,NULL);
	pthread_cond_init(&tp->full,NULL);
	pthread_cond_init(&tp->null,NULL);
	return tp;
}

// 销毁线程池
void tp_destory(ThreadPool* tp)
{
	for(int i=0; i<tp->thread_cnt; i++)
	{
		pthread_cancel(tp->tid[i]);
	}
	free(tp->tid);
	destory_queue(tp->queue);
	free(tp);
}

void* run(void* arg)
{
	ThreadPool* tp = arg;

	for(;;)
	{
		void* ptr = tp_pop(tp);
		tp->task(ptr);
	}
}

// 启动
void start(ThreadPool* tp)
{
	for(int i=0; i<tp->thread_cnt; i++)
	{
		pthread_create(&tp->tid[i],NULL,run,tp);
		printf("启动线程：%lu\n",tp->tid[i]);
	}
}

// 生产
void tp_push(ThreadPool* tp,void* ptr)
{
	pthread_mutex_lock(&tp->mutex);
	while(full_queue(tp->queue))
	{
		pthread_cond_wait(&tp->full,&tp->mutex);
	}
	printf("tp_push:%p\n",ptr);

	push_queue(tp->queue,ptr);
	pthread_mutex_unlock(&tp->mutex);
	pthread_cond_signal(&tp->null);
}

// 消费
void* tp_pop(ThreadPool* tp)
{
	pthread_mutex_lock(&tp->mutex);
	while(empty_queue(tp->queue))
	{
		pthread_cond_wait(&tp->null,&tp->mutex);
	}

	void* ptr = pop_queue(tp->queue);
	printf("tp_pop:%p\n",ptr);

	pthread_mutex_unlock(&tp->mutex);
	pthread_cond_signal(&tp->full);
	return ptr;
}
