#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#include <stdio.h>
#include <stdbool.h>

typedef struct ArrayQueue
{
	void** arr;	// 数据存储区域
	size_t cal;	// 队列的容量
	size_t cnt;	// 元素的数量
	int head;	// 队头下标
	int tail;	// 队尾下标
}ArrayQueue;

// 创建
ArrayQueue* create_queue(size_t cal);
// 销毁
void destory_queue(ArrayQueue* queue);
// 队空
bool empty_queue(ArrayQueue* queue);
// 队满
bool full_queue(ArrayQueue* queue);
// 入队
bool push_queue(ArrayQueue* queue,void* ptr);
// 出队
void* pop_queue(ArrayQueue* queue);

#endif//ARRAY_QUEUE_H
