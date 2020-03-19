#include "philo_one.h"

/*
** send an error in stderr_fileno as:
** "prg_name: msg_error"
*/

void	msg_error(char *prg_name, char *msg)
{
	write(STDERR_FILENO, prg_name, ft_strlen(prg_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

/*
** call msg_error by corresponding the given error code "error" with a message
*/

int		throw_error(char *prg_name, int error)
{
	if (error == TOO_MANY_ARGS)
		msg_error(prg_name, "Wrong number of arguments");
	else if (error == WRONG_ARG)
		msg_error(prg_name, "Wrong argument");
	else if (error = ERROR_MALLOC)
		msg_error(prg_name, "malloc error");
	return (error);
}
