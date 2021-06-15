#ifndef MALLOC_H
# define MALLOC_H

# include <sys/time.h>
# include <sys/resource.h>
# include <sys/mman.h>
# include <stdint.h>
# include <unistd.h>

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

// 1432005180
// 0101 0101 0101 1010 1010 1010 0011 1100
# define MAGIC_N					0x555AAA3C
# define PAGE_TINY_SIZE				(16 * getpagesize())
# define BLOCK_TINY_LIMIT			1024
# define PAGE_SMALL_SIZE			(128 * getpagesize())
# define BLOCK_SMALL_LIMIT			8192

# define STRUCT_MAIN_PAGE_SIZE		(size_t)(sizeof(t_main_page))
# define STRUCT_PAGE_SIZE			(size_t)(sizeof(t_page))
# define STRUCT_BLOCK_SIZE			(size_t)(sizeof(t_block))

typedef void						*t_v;
typedef char						*t_ch;

# define PAGE_UNUSED_ADDR(p)		((t_v)((t_ch)(p) + STRUCT_PAGE_SIZE))

# define PAGE_LAST_ADDR(p)			((t_ch)p + p->size)
# define BLOCK_LAST_ADDR(b, a)		((t_ch)b + STRUCT_BLOCK_SIZE + a)
# define BLOCK_FIRST_ADDR(b)		((t_block *)((t_ch)b - STRUCT_BLOCK_SIZE))

# define AVAILABLE					1
# define UNAVAILABLE				0

typedef struct		s_main_page
{
	struct s_page	*tiny_head;
	struct s_page	*tiny_last;
	struct s_page	*small_head;
	struct s_page	*small_last;
	struct s_page	*large_head;
	struct s_page	*large_last;
}					t_main_page;

typedef enum		e_page_type
{
	P_TINY,
	P_SMALL,
	P_LARGE
}					t_page_type;

typedef struct		s_page
{
	size_t			size;
	size_t			block_unvail_qt;
	t_page_type		type;
	struct s_page	*prev;
	struct s_page	*next;
	struct s_block	*block_head;
}					t_page;

typedef struct		s_block
{
	size_t			magic_num;
	size_t			size;
	int				avail;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

/* GENERAL--------------------------------------------------------------------*/
void		*malloc(size_t area_size);
void		free(void *ptr);
void		*realloc(void *ptr, size_t area_size);
void		*alloc_memory(const size_t page_size);
t_block		*block_validation(t_page *page, void *ptr);
t_page		*page_validation(void *ptr);

/* PAGE-----------------------------------------------------------------------*/
t_main_page	*main_page_get(void);
void		main_page_update(t_page *page);
t_page		*page_get_available(const size_t block_size);
t_page		*page_create(const size_t size);

/* BLOCK----------------------------------------------------------------------*/
t_block		*block_get_available(t_page *page, const size_t area_size);
void		block_reserve(t_page *page, t_block *block, const size_t area_size);
t_block		*block_place(void *page, const size_t area_size);

/* DEBUG----------------------------------------------------------------------*/
void		show_alloc_mem(void);

# endif
