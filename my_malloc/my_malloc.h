#ifndef MY_MALLOC
#define MY_MALLOC
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <stdc-predef.h>
#include <string.h>
#include <assert.h>

/*  declare chunk  */
typedef struct lump {
	size_t  chunk_size;
	struct lump *next;
	struct lump *prev;
	struct lump *next_free;
	struct lump *prev_free;
} lump;

/*  declare blocklist    */
typedef struct blocklist {
	lump *_first_chunk;
	lump *_last_chunk;
	lump *_first_free_chunk;
	lump *_last_free_chunk;
	size_t allocated;
} blocklist;

/*  declare block  */
typedef struct
{
    void *begin;
    size_t size;
} block;

/*  declare chunks list    */
typedef struct
{
    size_t numb;
    block chunk[1024];
} chunk_list;


void* my_malloc(size_t size);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size);
void my_free(void *ptr);


#endif //MY_MALLOC_HDR