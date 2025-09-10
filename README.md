# Pipex

A Unix pipeline implementation that simulates shell command piping behavior using system calls.

## Description

Pipex recreates the functionality of shell pipes by implementing `< file1 cmd1 | cmd2 > file2` using low-level system calls. The program creates two processes connected by a pipe, where the first process executes `cmd1` reading from `file1`, and the second process executes `cmd2` writing to `file2`.

## Features

- **Process Management**: Uses `fork()` to create child and parent processes
- **Inter-Process Communication**: Implements pipes for process communication
- **File Redirection**: Redirects stdin/stdout using `dup2()`
- **Command Execution**: Executes shell commands with `execve()`
- **Error Handling**: Comprehensive error checking for system calls
- **Memory Management**: Proper memory allocation and cleanup
- **Path Resolution**: Automatically finds executables in PATH

## Usage

```bash
# Compile
make

# Execute
./pipex file1 cmd1 cmd2 file2
```

### Example

```bash
# Create test file
echo "Hello World" > input.txt

# Use pipex (equivalent to: < input.txt cat | wc -w > output.txt)
./pipex input.txt "cat" "wc -w" output.txt

# Check result
cat output.txt  # Should output: 2
```

## Technical Implementation

### Architecture
```
┌─────────┐    ┌─────┐    ┌──────┐    ┌─────┐    ┌─────────┐
│ file1   │───▶│cmd1 │───▶│ pipe │───▶│cmd2 │───▶│ file2   │
│(input)  │    │     │    │      │    │     │    │(output) │
└─────────┘    └─────┘    └──────┘    └─────┘    └─────────┘
     ▲           ▲                                    ▲
     │           │                                    │
Child Process  Child Process                    Parent Process
```

### System Calls Used
- `pipe()` - Creates communication channel between processes
- `fork()` - Creates child process
- `dup2()` - Redirects file descriptors
- `execve()` - Replaces process with executable
- `open()` - Opens files
- `close()` - Closes file descriptors

### Process Flow
1. **Setup**: Parse arguments and validate files
2. **Path Resolution**: Find executable paths in environment PATH
3. **Pipe Creation**: Create pipe for inter-process communication
4. **Fork**: Split into parent and child processes
5. **Child Process**: 
   - Redirects stdin to input file
   - Redirects stdout to pipe
   - Executes first command
6. **Parent Process**:
   - Redirects stdin to pipe
   - Redirects stdout to output file  
   - Executes second command

## Project Structure

```
pipex/
├── src/
│   ├── main.c          # Argument parsing, path resolution
│   └── pipex.c         # Core pipe implementation
├── utils/
│   ├── ft_free.c       # Memory management
│   ├── ft_split.c      # String splitting
│   ├── ft_strlen.c     # String length
│   ├── ft_strdup.c     # String duplication
│   ├── ft_strjoin.c    # String concatenation
│   ├── ft_strncmp.c    # String comparison
│   └── ft_substr.c     # Substring extraction
├── includes/
│   └── pipex.h         # Header file
├── ft_printf/          # Custom printf library
└── makefile           # Build configuration
```

## Compilation

The project uses a custom Makefile with the following targets:

- `make` - Builds the executable
- `make clean` - Removes object files
- `make fclean` - Removes all generated files
- `make re` - Rebuilds everything

## Requirements

- Unix-like operating system (Linux, macOS)
- GCC compiler
- Standard C library
- POSIX-compliant system calls

## Error Handling

The program handles various error conditions:

- Invalid number of arguments
- Non-existent input files
- Permission denied errors
- Command not found errors
- Pipe creation failures
- Fork failures
- File descriptor errors

## Memory Management

- All dynamically allocated memory is properly freed
- No memory leaks (verified with Valgrind)
- Proper cleanup on program termination

## Academic Project

This project is part of the 42 School curriculum, focusing on:
- Unix system programming
- Process management
- Inter-process communication
- File descriptor manipulation
- Error handling in C

## Author

**samalves** - 42 Berlin

## License

This project is part of 42 School curriculum and follows their academic guidelines.
