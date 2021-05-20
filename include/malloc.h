#ifndef MALLOC_H
# define MALLOC_H

# include "malloc_errors.h"
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
// # include <limits.h>
# include <stdint.h>
# include <unistd.h>

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

// 1432005180
// 0101 0101 0101 1010 1010 1010 0011 1100
# define MAGIC_N					0x555AAA3C
# define PAGE_TINY_SIZE				(2 * getpagesize())
# define BLOCK_TINY_LIMIT			128
# define PAGE_SMALL_SIZE			(16 * getpagesize())
# define BLOCK_SMALL_LIMIT			1024

# define STRUCT_MAIN_PAGE_SIZE		(size_t)(sizeof(t_main_page))
# define STRUCT_PAGE_SIZE			(size_t)(sizeof(t_page))
# define STRUCT_BLOCK_SIZE			(size_t)(sizeof(t_block))

typedef void	*t_v;
typedef char	*t_ch;

# define PAGE_UNUSED_ADDR(p)		((t_v)((t_ch)(p) + STRUCT_PAGE_SIZE))

# define PAGE_LAST_ADDR(p)			((t_ch)p + p->size)
# define BLOCK_LAST_ADDR(b, a)		((t_ch)b + a + STRUCT_BLOCK_SIZE)
# define BLOCK_FIRST_ADDR(b)		((t_block *)((t_ch)b - STRUCT_BLOCK_SIZE))

# define AVAILABLE					1
# define UNAVAILABLE				0

// вспомнить бы для чего эта хуета
# define PTR_NENMEM					((void *) - 1)

typedef enum				e_page_type
{
	E_TINY,
	E_SMALL,
	E_LARGE
}							t_page_type;

typedef struct				s_main_page
{
	struct s_page			*tiny_head;
	struct s_page			*small_head;
	struct s_page			*large_head;
}							t_main_page;

// новый лист добавляется в начало и становится head-листом
typedef struct				s_page
{
	size_t					size;
	size_t					avail_size;				//удалить потом
	size_t					allocated_blocks;
	struct s_page			*next;
	struct s_block			*block_head;
	t_page_type				type;
}							t_page;

typedef struct				s_block
{
	unsigned int			magic_num; //0x5FA
	size_t					size;
	struct s_block			*prev;
	struct s_block			*next;
	struct s_page			*page;
	int						is_avail;
}							t_block;

/* GENERAL--------------------------------------------------------------------*/
void				*m_malloc(size_t size);
void				m_free(void *ptr);
void				*allocate_memory(const size_t size);

/* PAGE-----------------------------------------------------------------------*/
t_main_page			*main_page_get(void);
t_page				*page_get_available(const size_t block_size);
t_page				*page_create(const size_t size);
t_page				*page_get_current_by_type(const size_t block_size);

/* BLOCK----------------------------------------------------------------------*/
t_block				*block_get_available(const t_page *page, const size_t block_size);
t_block				*block_add(void *page, const size_t area_size);

/* DEBUG----------------------------------------------------------------------*/
void				dbg_block(t_block *block);
void				dbg_page(t_page *page);
void				dbg_count_blocks_in_page(const t_page *page);
void				dbg_count_pages(const t_page_type type);
void				dbg_gfinfo(const t_page_type type);

# endif
