#include "../include/malloc.h"

void *g_e_rewrite;

void				*allocate_memory(const size_t page_size)
{
	void			*data_memory;

	data_memory = mmap(NULL,
						page_size,
						PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANON,
						-1,
						0);
	if (data_memory == MAP_FAILED)
		return (NULL);
	return (data_memory);
}

size_t	area_size_align(size_t area_size)
{
	if (((((area_size - 1) / BITW) * BITW) + BITW) < area_size)
	{
		dprintf(2, "ERROR: OVERFLOW OCCURED IN [%s]\n", __func__);
		return (0);
	}
	return ((((area_size - 1) / BITW) * BITW) + BITW);
}

void	*m_malloc(size_t area_size)
{
	t_page		*page;
	t_block		*block;

	if (!(area_size = area_size_align(area_size)))
		return (NULL);
	page = page_get_available(area_size);
	if (!(block = block_get_available(page, area_size)))
	{
		if (g_e_rewrite)
		{
			dprintf(2, "Error: block rewriting detected");
			dprintf(2, " at [%p], stop work\n", g_e_rewrite);
			return (NULL);
		}
		page = page_create(area_size);
		if (!(block = block_get_available(page, area_size)))
			return (NULL);
		// printf("СТРАНИЧКА ЗАКОНЧИЛАСЬ !!!!!!!\n");
	}
	return ((t_v)BLOCK_LAST_ADDR(block, 0));
}

// 8192
// 65536
int			main()
{
	void *p1 = NULL;
	void *p2 = NULL;
	// void *p3 = NULL;
	// void *p4 = NULL;
	// void *p5 = NULL;
	// void *p6 = NULL;
	// void *p7 = NULL;
	// void *p8;
	// void *p9;
	// void *p10;
	// void *p11;


	// TINY 
	p1 = m_malloc(7);
		// goto KEK;
	printf("%p\n", (t_v)BLOCK_FIRST_ADDR(p1));
	bzero(BLOCK_FIRST_ADDR(p1), STRUCT_BLOCK_SIZE);
	p2 = m_malloc(8);
	// if (!(p2 = m_malloc(1280)))
		// goto KEK;
	// if (!(p3 = m_malloc(1000)))
		// goto KEK;
	// goto KEK;
	// KEK:
	// {
	// }
	dbg_gfinfo(E_TINY);
	dbg_gfinfo(E_SMALL);
	dbg_gfinfo(E_LARGE);
	// dbg_count_pages(E_TINY);
	// dbg_count_pages(E_SMALL);
	// dbg_count_pages(E_LARGE);
	return (0);
}

/*
int main() { 
  
    struct rlimit old_lim, lim, new_lim; 
  
    // Get old limits 
    if( getrlimit(RLIMIT_DATA, &old_lim) == 0) 
        printf("Old limits -> soft limit= %ld \t"
           " hard limit= %ld \n", old_lim.rlim_cur,  
                                 old_lim.rlim_max); 
    else
        fprintf(stderr, "%s\n", strerror(errno)); 
      
    // Set new value 
    lim.rlim_cur = 3; 
    lim.rlim_max = 1024; 
  
    // Set limits 
    if(setrlimit(RLIMIT_NOFILE, &lim) == -1) 
        fprintf(stderr, "%s\n", strerror(errno)); 
      
    // Get new limits 
    if( getrlimit(RLIMIT_NOFILE, &new_lim) == 0) 
        printf("New limits -> soft limit= %ld "
         "\t hard limit= %ld \n", new_lim.rlim_cur,  
                                  new_lim.rlim_max); 
    else
        fprintf(stderr, "%s\n", strerror(errno)); 
    return 0; 
} 
*/

// */

/* PAGESIZE is POSIX: http://pubs.opengroup.org/onlinepubs/9699919799/
     * but PHYS_PAGES and AVPHYS_PAGES are glibc extensions. I bet those are
     * parsed from /proc/meminfo. */
// printf(
//     "sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE) = 0x%lX\n",
//     sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE)
// );
// printf(
//     "sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE) = 0x%lX\n",
//     sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE)
// );

// /* glibc extensions. man says they are parsed from /proc/meminfo. */
// printf(
//     "get_phys_pages() * sysconf(_SC_PAGESIZE) = 0x%lX\n",
//     get_phys_pages() * sysconf(_SC_PAGESIZE)
// );
// printf(
//     "get_avphys_pages() * sysconf(_SC_PAGESIZE) = 0x%lX\n",
//     get_avphys_pages() * sysconf(_SC_PAGESIZE)
// );
