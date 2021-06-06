#include "../include/malloc.h"

// static void	main_page_update_extra(t_page **head, t_page **last, t_page *new)
// {
// 	if (!*head)
// 		*head = new;
// 	if (*last)
// 	{
// 		(*last)->next = new;
// 		new->prev = *last;
// 	}
// 	*last = new;
// }

// void	main_page_update(t_page *page)
// {
// 	t_main_page	*m_page;

// 	m_page = main_page_get();
// 	switch (page->type)
// 	{
// 	case E_TINY:
// 		main_page_update_extra(&m_page->tiny_head, &m_page->tiny_last, page);
// 		break;
// 	case E_SMALL:
// 		main_page_update_extra(&m_page->small_head, &m_page->small_last, page);
// 		break;
// 	case E_LARGE:
// 		main_page_update_extra(&m_page->large_head, &m_page->large_last, page);
// 		break;
// 	}
// }

static void	main_page_update_extra(t_page **head_old, t_page *head_new)
{
	t_page *temp;

	temp = *head_old;
	*head_old = head_new;
	head_new->next = temp;
}

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

/*
** main_page_get():
**
** Возвращает адрес статической структуры, которая хранит информацию о страницах разных типов
*/

t_main_page	*main_page_get(void)
{
	static t_main_page	main_page;

	return (&main_page);
}
