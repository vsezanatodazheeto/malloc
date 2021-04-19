
#ifndef MALLOC_ERRORS_H
# define MALLOC_ERRORS_H

# include <stddef.h>

# define ERR_MALLOC			"error in malloc: "
# define ERR_MAIN_PAGE		"couldn't create main_page\n"

void				*error_to_stderr(const char *str, size_t str_size);

#endif
