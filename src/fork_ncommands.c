#include "../includes/pipex.h"

int	fork_ncommands(int count, t_data *data, char *envp[])
{
	data->file_path = file_found(data->args[count][0]);
	printf("%s\n", data->file_path);
	printf("count: %d\n", count);
	data->pids[count] = fork();
	if (data->pids[count] == -1)
		handle_errors(3, data);
	if (data->pids[count] == 0)
	{
		if (count == 0)
			dup2(data->file_in, STDIN_FILENO);
		else
			dup2(data->fd[0], STDIN_FILENO);
		if (count + 1 == data->cmds_list)
			dup2(data->file_out, STDOUT_FILENO);
		else
			dup2(data->fd[1], STDOUT_FILENO);
		write(2, "hey\n", 4);
		close(data->fd[1]);
		close(data->fd[0]);
		close(data->file_in);
		close(data->file_out);
		execve(data->file_path, data->args[count], envp);
	}
	return (count);
}