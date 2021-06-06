#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_unpd
{
	int				gsex;
	struct s_unpd	*next;
	struct s_unpd	*prev;
}					t_unpd;

# define L_ELEM_LOC(p_n, p)	((size_t)((char *)p_n - (char *)p))

static void *list_create(size_t size)
{
	char *ptr;

	if ((ptr = (char *)malloc(size)))
		memset(ptr, 0, size);
	return (ptr);
}

void	*list_l_add_front(void **head, size_t next, size_t size)
{
	char	*ptr;

	if (!(ptr = list_create(size)))
		return (NULL);
	if (!*head)
		*head = ptr;
	else
	{
		memcpy(ptr + next, head, sizeof(void *));
		*head = ptr;
	}
	return (ptr);
}

void	*list_dl_add_front(void **head, size_t next, size_t prev, size_t size)
{
	char	*ptr;

	if (!(ptr = list_create(size)))
		return (NULL);
	if (*head)
	{
		memcpy(ptr + next, head, sizeof(void *));
		memcpy(*head + prev, &ptr, sizeof(void *));
	}
	*head = ptr;
	return (ptr);
}

void	*list_l_add_back(void **last, size_t next, size_t size)
{
	char *ptr;

	if (!(ptr = list_create(size)))
		return (NULL);
	if (*last)
		memcpy(*last + next, &ptr, sizeof(void *));
	*last = ptr;
	return (ptr);
}

void	*list_dl_add_back(void **last, size_t next, size_t prev, size_t size)
{
	char *ptr;

	if (!(ptr = list_create(size)))
		return (NULL);
	if (*last)
	{
		memcpy(*last + next, &ptr, sizeof(void *));
		memcpy(ptr + prev, last, sizeof(void *));
	}
	*last = ptr;
	return (ptr);
}


int main()
{
	t_unpd *head = NULL, *last = NULL, *temp = NULL;

	// l_list_add_front((void *)&u, (char *)&(u->next) - (char *)u, sizeof(*u));
	// l_list_add_front((void *)&u, (char *)&(u->next) - (char *)u, sizeof(*u));
	// l_list_add_front((void *)&u, (char *)&(u->next) - (char *)u, sizeof(*u));

	for (int i = 0; i < 10; i++)
	{
		list_dl_add_front((void *)&head, L_ELEM_LOC(&(head->next), &head), (char *)&(head->prev) - (char *)head, sizeof(*head));
		head->gsex = i;
		// list_dl_add_back((void *)&last, (char *)&(head->next) - (char *)head, (char *)&(head->prev) - (char *)head, sizeof(*head));
		// if (!head)
			// head = last;
		// last->gsex = i;
	}
	for (; head; head = head->next)
	{
		if (!head->next)
			last = head;
		printf("%d: %p\n", head->gsex, (void *)head);
	}
	printf("-----------------\n");
	for (; last; last = last->prev)
		printf("%d: %p\n", last->gsex, (void *)last);
	exit(0);
}
