#include "../include/malloc.h"

static void	main_page_update_extra(t_page **head_old, t_page *head_new)
{
	t_page *temp;

	temp = *head_old;
	*head_old = head_new;
	head_new->next = temp;
}

// main_page_update:
// a.k.a push front

void	main_page_update(t_page *page)
{
	t_main_page	*m_page;

	m_page = main_page_get();
	switch (page->type)
	{
	case E_TINY:
		main_page_update_extra(&m_page->tiny_head, page);
		break;
	case E_SMALL:
		main_page_update_extra(&m_page->small_head, page);
		break;
	case E_LARGE:
		main_page_update_extra(&m_page->large_head, page);
		break;
	}
}

// main_page_get:
// returns the address of a static structure that stores information about pages of different types

t_main_page	*main_page_get(void)
{
	static t_main_page	main_page;

	return (&main_page);
}
