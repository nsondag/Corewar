#include "vm_corewar.h"

char				(*args)[2] = {
	"-dump",
	"-n"
};

int					ft_error_invalid_arg()
{
	return (-1);
}

void				ft_handle_dump(char *arg)
{
	return ;
}

int					main(int argc, char **argv)
{
	int				i;

	if (argc < 4)
		return (ft_error_invalid_arg());
	if (!ft_strcmp(args[0], argv[1]))
	{
		ft_handle_dump(argv[2]);
		i = 5;
	}
	else
		i = 3;
	while (i < argc)
	{
		if (ft_strcmp(args[1], argv[i - 2]))
			return (ft_error_invalid_arg());
		parse_champ(argv[i - 1], argv[i]);
		i += 3;
	}
	return (0);
}