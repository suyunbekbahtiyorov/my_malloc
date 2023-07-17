#include "my_malloc.h"
#include <stdlib.h>

static blocklist *selection = NULL;

char stack[640000] = {0};

chunk_list alloced_chunks = {0};

chunk_list liberate_chks = {
    .numb = 1,
    .chunk = {
        {
            .begin = stack,
            .size = sizeof(stack)
        }
    }
};

chunk_list tmp_chks = {0};

size_t chunk_list_ = 1024;

void *my_malloc(size_t size)
{
    tmp_chks.numb = 0;
    for(size_t i=0; i < liberate_chks.numb; i++)
    {
        block chunk = liberate_chks.chunk[i];
        if(tmp_chks.numb > 0)
        {
            block *top_chunk = &tmp_chks.chunk[tmp_chks.numb - 1];

            if((size_t)top_chunk->begin + top_chunk->size == (size_t)chunk.begin)
            {
                top_chunk->size += chunk.size;
            }
            else
            {
                assert(tmp_chks.numb < chunk_list_);
                tmp_chks.chunk[tmp_chks.numb].begin = chunk.begin;
                tmp_chks.chunk[tmp_chks.numb].size = chunk.size;
                for (size_t i = tmp_chks.numb; i > 0 && tmp_chks.chunk[i].begin < tmp_chks.chunk[i - 1].begin; i--)
                {
                    block t = tmp_chks.chunk[i];
                    tmp_chks.chunk[i] = tmp_chks.chunk[i - 1];
                    tmp_chks.chunk[i - 1] = t;
                }
                tmp_chks.numb++;
            }
        }
        else
        {
            assert(tmp_chks.numb < chunk_list_);
            tmp_chks.chunk[tmp_chks.numb].begin = chunk.begin;
            tmp_chks.chunk[tmp_chks.numb].size = chunk.size;
            i = tmp_chks.numb;
            while(i > 0 && tmp_chks.chunk[i].begin < tmp_chks.chunk[i - 1].begin)
            {
                block t = tmp_chks.chunk[i];
                tmp_chks.chunk[i] = tmp_chks.chunk[i - 1];
                tmp_chks.chunk[i - 1] = t;
                i--;
            }
            tmp_chks.numb++;
        }
    }
    liberate_chks = tmp_chks;
    if (size > 0)
    {
        for (size_t i = 0; i < liberate_chks.numb; ++i)
        {
            block chunk = liberate_chks.chunk[i];
            if (chunk.size > size)
            {
                int j = i;
                while ( j < (int)liberate_chks.numb - 1)
                {
                    liberate_chks.chunk[i] = liberate_chks.chunk[j + 1];
                    j++;
                }
                size_t tail_size = chunk.size - size;
                assert(alloced_chunks.numb < chunk_list_);
                alloced_chunks.chunk[alloced_chunks.numb].begin = chunk.begin;
                alloced_chunks.chunk[alloced_chunks.numb].size = size;
                for (size_t i = alloced_chunks.numb;
                    i > 0 && alloced_chunks.chunk[i].begin < alloced_chunks.chunk[i - 1].begin; --i)
                {
                    block t = alloced_chunks.chunk[i];
                    alloced_chunks.chunk[i] = alloced_chunks.chunk[i - 1];
                    alloced_chunks.chunk[i - 1] = t;
                }
                alloced_chunks.numb += 1;
                if (tail_size > 0)
                {
                    assert(liberate_chks.numb < chunk_list_);
                    liberate_chks.chunk[liberate_chks.numb].begin = (void*)((size_t)chunk.begin + size);
                    liberate_chks.chunk[liberate_chks.numb].size = tail_size;
                    i = liberate_chks.numb;
                    while (i > 0 && liberate_chks.chunk[i].begin < liberate_chks.chunk[i - 1].begin)
                    {
                        block t = liberate_chks.chunk[i];
                        liberate_chks.chunk[i] = liberate_chks.chunk[i - 1];
                        liberate_chks.chunk[i - 1] = t;
                        i--;
                    }
                    liberate_chks.numb += 1;
                }
                return chunk.begin;
            }
        }
    }
    return NULL;
}

void *my_calloc(size_t nmemb, size_t size)
{
	tmp_chks.numb = 0;
    for(size_t i=0; i < liberate_chks.numb; i++)
    {
        block chunk = liberate_chks.chunk[i];
        if(tmp_chks.numb > 0)
        {
            block *top_chunk = &tmp_chks.chunk[tmp_chks.numb - 1];

            if((size_t)top_chunk->begin + top_chunk->size == (size_t)chunk.begin)
            {
                top_chunk->size += chunk.size;
            }
            else
            {
                assert(tmp_chks.numb < chunk_list_);
                tmp_chks.chunk[tmp_chks.numb].begin = chunk.begin;
                tmp_chks.chunk[tmp_chks.numb].size = chunk.size;
                for (size_t i = tmp_chks.numb; i > 0 && tmp_chks.chunk[i].begin < tmp_chks.chunk[i - 1].begin; i--)
                {
                    block t = tmp_chks.chunk[i];
                    tmp_chks.chunk[i] = tmp_chks.chunk[i - 1];
                    tmp_chks.chunk[i - 1] = t;
                }
                tmp_chks.numb++;
            }
        }
        else
        {
            assert(tmp_chks.numb < chunk_list_);
            tmp_chks.chunk[tmp_chks.numb].begin = chunk.begin;
            tmp_chks.chunk[tmp_chks.numb].size = chunk.size;
            i = tmp_chks.numb;
            while(i > 0 && tmp_chks.chunk[i].begin < tmp_chks.chunk[i - 1].begin)
            {
                block t = tmp_chks.chunk[i];
                tmp_chks.chunk[i] = tmp_chks.chunk[i - 1];
                tmp_chks.chunk[i - 1] = t;
                i--;
            }
            tmp_chks.numb++;
        }
    }
    liberate_chks = tmp_chks;
    if (nmemb*size > 0)
    {
        for (size_t i = 0; i < liberate_chks.numb; ++i)
        {
            block chunk = liberate_chks.chunk[i];
            if (chunk.size > nmemb*size)
            {
                int j = i;
                while ( j < (int)liberate_chks.numb - 1)
                {
                    liberate_chks.chunk[i] = liberate_chks.chunk[j + 1];
                    j++;
                }
                size_t tail_size = chunk.size - nmemb*size;
                assert(alloced_chunks.numb < chunk_list_);
                alloced_chunks.chunk[alloced_chunks.numb].begin = chunk.begin;
                alloced_chunks.chunk[alloced_chunks.numb].size = nmemb*size;
                for (size_t i = alloced_chunks.numb;
                    i > 0 && alloced_chunks.chunk[i].begin < alloced_chunks.chunk[i - 1].begin; --i)
                {
                    block t = alloced_chunks.chunk[i];
                    alloced_chunks.chunk[i] = alloced_chunks.chunk[i - 1];
                    alloced_chunks.chunk[i - 1] = t;
                }
                alloced_chunks.numb += 1;
                if (tail_size > 0)
                {
                    assert(liberate_chks.numb < chunk_list_);
                    liberate_chks.chunk[liberate_chks.numb].begin = (void*)((size_t)chunk.begin + nmemb*size);
                    liberate_chks.chunk[liberate_chks.numb].size = tail_size;
                    i = liberate_chks.numb;
                    while (i > 0 && liberate_chks.chunk[i].begin < liberate_chks.chunk[i - 1].begin)
                    {
                        block t = liberate_chks.chunk[i];
                        liberate_chks.chunk[i] = liberate_chks.chunk[i - 1];
                        liberate_chks.chunk[i - 1] = t;
                        i--;
                    }
                    liberate_chks.numb += 1;
                }
                return chunk.begin;
            }
        }
    }
    return NULL;
}

void my_free(void *ptr)
{
    if (ptr != NULL)
    {
        int ind;
        size_t i =0;
        while( i < alloced_chunks.numb) {
            if(alloced_chunks.chunk[i].begin == ptr)
            {
                ind = (int)i;
            }
            if(i == alloced_chunks.numb-1)
            {
                ind = -1;
            }
            i++;
        }
        assert(liberate_chks.numb < chunk_list_);
        liberate_chks.chunk[liberate_chks.numb].size = alloced_chunks.chunk[ind].size;
        liberate_chks.chunk[liberate_chks.numb].begin = alloced_chunks.chunk[ind].begin;
        i = liberate_chks.numb;
        while ( i > 0 && liberate_chks.chunk[i].begin < liberate_chks.chunk[i - 1].begin)
        {
            const block t = liberate_chks.chunk[i];
            liberate_chks.chunk[i] = liberate_chks.chunk[i - 1];
            liberate_chks.chunk[i - 1] = t;
            i--;
        }
        liberate_chks.numb += 1;
        i = ind;
        while( i < alloced_chunks.numb-1)
        {
            alloced_chunks.chunk[i] = alloced_chunks.chunk[i + 1];
            i++;
        }
        alloced_chunks.numb -= 1;
    }
}

void *my_realloc(void *ptr, size_t size)
{
	if ( !ptr )
    {
		return my_malloc(size);
	} else if (size == 0)
    {
		my_free(ptr);
        my_free(ptr);
		return NULL;
	}
	lump *c = (lump*)((char*)ptr - sizeof(lump) );
	if ( c < selection->_first_chunk || c > selection->_last_chunk + selection->_last_chunk->chunk_size )
    {
		fprintf(stderr, "%p is not a reallocatable memory space.\n", ptr);
        		return NULL;
	}
	if (size > c->chunk_size)
    {
		if (c->next->chunk_size + sizeof(lump) + c->chunk_size >= size)
        {
			lump *n, *p, *c2;
			c2 = c->next;
			n = c2->next;
		    	p = c2->prev;
			p->next = n;
			if (n)
            {
                n->prev = p;
            } 
			if (selection->_last_chunk == c2)
            {
                selection->_last_chunk = c2->prev;
            }
			n = c2->next_free;
			p = c2->prev_free;
			p->next_free = n;
			if (n)
            {
                n->prev_free = p;
            } 
			if (selection->_last_free_chunk == c2)
            {
                selection->_last_free_chunk = c2->prev_free;
            }
			if (selection->_first_free_chunk == c2)
            {
                selection->_first_free_chunk = c2->next_free;
            }
			c->chunk_size += c2->chunk_size + sizeof(lump);

			selection->allocated--;
		}
        else
        {
			int *new_mem = my_malloc( size );

			if (!new_mem)
            {
                return NULL;
            }
			int i = 0, n = c->chunk_size / sizeof(int);
			for (; i < n; i++)
            {
                new_mem[i] = ((int*)ptr)[i];
            } 
			my_free(ptr);
			ptr = (void*)new_mem;
		}
	}
	return ptr;
}

int main()
{
	char* str = (char*)my_malloc(6);
    str = "Hello";
    printf("%s\n", str);

    /* Test my_calloc */
    int *arrint = (int*)my_calloc(4, sizeof(int));
    for(int i=0; i < 4; i++)
    {
        arrint[i] = 77;
    }
    for(int i=0; i < 4; i++)    // output numbers
    {
        printf("\t%d", arrint[i]);
    }
    putchar('\n');
        

    /*   Test my_realloc   */
    float *arrfloat = (float*)my_calloc(3 , sizeof(float)); 
    for(int i=0; i<3; i++)
    {
        arrfloat[i] = 9.99;
    } 
    char* ptr = (char*)my_malloc(6);
    for(int i = 0 ; i < 6 ; i ++)
    {
        ptr[i] = i;
    }

    for(int i = 0 ; i < 6 ; i ++)
    {
        printf("%d", ptr[i]);  // output numbers
    }
    
    putchar('\n');
    /*  Test my_free */
    my_free(str);
    my_free(arrint);
    my_free(arrfloat);
    my_free(ptr);
}