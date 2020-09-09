#include <stdlib.h>
#include "array_queue.h"

// 创建
ArrayQueue* create_queue(size_t cal)
{
	ArrayQueue* queue = malloc(sizeof(ArrayQueue));
	queue->arr = malloc(sizeof(void*)*cal);
	queue->cal = cal;
	queue->cnt = 0;
	queue->head = 0;
	queue->tail = 0;
	return queue;
}

// 销毁
void destory_queue(ArrayQueue* queue)
{
	free(queue->arr);
	free(queue);
}

// 队空
bool empty_queue(ArrayQueue* queue)
{
	return !queue->cnt;
}

// 队满
bool full_queue(ArrayQueue* queue)
{
	return queue->cnt >= queue->cal;
}

// 入队
bool push_queue(ArrayQueue* queue,void* ptr)
{
	if(full_queue(queue)) return false;
	queue->arr[queue->tail++] = ptr;
	queue->tail %= queue->cal;
	queue->cnt++;
	return true;
}

// 出队
void* pop_queue(ArrayQueue* queue)
{
	if(empty_queue(queue)) return NULL;
	void* ptr = queue->arr[queue->head];
	queue->arr[queue->head++] = NULL;
	queue->head %= queue->cal;
	queue->cnt--;
	return ptr;
}
