void		ft_parseng(t_all *all, t_op a, t_operation op)
{
	char		*v;
	unsigned	j;
	int			f;
	int			k;

	j = 0;
	k = a.arg_q - 1;
	all->i += ft_strlen((char *)a.cmd);
	while (j < 3)
	{
		SPLIT[all->i] == SEPARATOR_CHAR ? ++all->i : 0;
		f = 0;
		if (!a.arg_type[j])
			++j;
		else
		{
			v = tablica(a.arg_type[j]);
			quick_pass(all);
			v[0] == 1 ? f = ft_idir(all, &k, IND_SIZE) : 0;
			!f && v[1] == 1 ? f = ft_dir(all, &k, op) : 0;
			!f && v[2] == 1 ? f = ft_reg(all, &k, T_REG) : 0;
			free(v);
			if (!f)
			{
				ft_error(all, Syntactic, Wrong_argument);
				while (SPLIT[all->i] && SPLIT[all->i] != ',' &&
					SPLIT[all->i] != ' ' && SPLIT[all->i] != '\t')
					++all->i;
			}
			++j;
		}
	}
	last_check(all) ? ft_error(all, Syntactic, Odd_argument) : 0;
}