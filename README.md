# pipex
A Unix pipeline implementation in C that mimics shell command piping. Creates two processes connected by a pipe to execute &lt; file1 cmd1 | cmd2 > file2. Features proper error handling, memory management, and process synchronization using fork(), pipe(), dup2(), and execve().
