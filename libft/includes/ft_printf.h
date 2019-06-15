/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 03:47:46 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/15 02:59:55 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include <stdlib.h>

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_BLUE	"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN	"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"
# define ANSI_COLOR_WHITE	"\x1b[37m"

# define MAX_BUF_SIZE	100
# define NINF c == c + c / .0 && c < 0
# define INF c == c + c / .0 && c > 0

typedef struct				s_format
{
	char			*str;
	va_list			arg;
	int				hp;
	int				t;
	char			sr[3];
	int				len;
	unsigned char	tp;
	unsigned char	hps : 1;
	unsigned char	st : 1;
	unsigned char	m : 1;
	unsigned char	pl : 1;
	unsigned char	pr : 1;
	unsigned char	o : 1;
	unsigned char	z : 1;
	char			buf[MAX_BUF_SIZE];
	int				b_i;
}							t_format;

typedef struct				s_format_d
{
	unsigned long long int	o;
	size_t					spase;
	size_t					zero;
	size_t					minus;
	size_t					plus;
	size_t					base;
	int						len;
	size_t					rd;
}							t_format_d;

int							ft_printf(char const *s, ...);
void						ft_flag(t_format *mod);
void						ft_tochnost(t_format *mod);
void						ft_hirina(t_format *mod);
void						ft_specr(t_format *mod);
void						write_and_zero(t_format *p);
void						ft_restor_p(t_format *p);

size_t						ft_start(t_format *mod);
size_t						ft_char(t_format *mod);
size_t						ft_printstr(t_format *mod);
void						ft_simup(t_format *p, size_t len, char c);
size_t						kol_sim(unsigned long long int d, size_t base);
void						itua_base_mod(t_format_d *d, t_format *p, size_t f);

/*
** printnbr int
*/

size_t						incd(t_format *mod, int len, int f, size_t n);
void						ft_format_d(t_format *p, t_format_d *d, int f);
size_t						ft_printnbr(t_format *p, long long k);
size_t						ft_printnbru(t_format *p, unsigned long long k);
size_t						ft_flag_d_i(t_format *p);
size_t						ft_flag_u(t_format *p);

/*
** print x
*/

size_t						ft_flag_x(t_format *mod);
size_t						ft_printx(t_format *p,
		unsigned long long int k, int f);

size_t						ft_charu(t_format *p, wint_t c);
size_t						ft_printstru(t_format *p);
size_t						ft_float(t_format *p);
size_t						ft_floatlong(t_format *p);
void						ft_sborfloat(t_format *p, t_format_d *d,
		int f, char *okr);
void						ft_incf(t_format *p, t_format_d *d, int f);
size_t						ft_nan(t_format *p, double c);
#endif
