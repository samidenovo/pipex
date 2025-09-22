# Pipex

A Unix pipeline implementation that simulates shell command piping behavior using system calls.

## Description

Pipex recreates the functionality of shell pipes by implementing pipeline commands using low-level system calls. The program supports both basic two-command pipelines (`< file1 cmd1 | cmd2 > file2`) and multiple command pipelines (`< file1 cmd1 | cmd2 | ... | cmdn > file2`).

## Features

- **Process Management**: Uses `fork()` to create multiple child processes
- **Inter-Process Communication**: Implements pipes for process communication
- **File Redirection**: Redirects stdin/stdout using `dup2()`
- **Command Execution**: Executes shell commands with `execve()`
- **Multiple Commands**: Supports unlimited number of commands in pipeline (bonus)
- **Error Handling**: Comprehensive error checking for system calls
- **Memory Management**: Proper memory allocation and cleanup
- **Path Resolution**: Automatically finds executables in PATH

## Usage

### Mandatory Version
```bash
# Compile
make

# Execute (equivalent to: < file1 cmd1 | cmd2 > file2)
./pipex file1 cmd1 cmd2 file2
```

### Bonus Version
```bash
# Compile bonus
make bonus

# Execute with multiple commands
./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
```

## Examples

### Basic Pipeline
```bash
# Create test file
echo "Hello World\nPipex Project" > input.txt

# Use pipex (equivalent to: < input.txt cat | wc -w > output.txt)
./pipex input.txt "cat" "wc -w" output.txt

# Check result
cat output.txt  # Should output: 4
```

### Multiple Commands (Bonus)
```bash
# Complex pipeline with 4 commands
./pipex_bonus input.txt "cat" "grep Hello" "wc -l" "cat" output.txt

# Equivalent shell command: < input.txt cat | grep Hello | wc -l | cat > output.txt
```

## Technical Implementation

### Basic Architecture (Mandatory)
```
┌─────────┐    ┌─────┐    ┌──────┐    ┌─────┐    ┌─────────┐
│ file1   │───▶│cmd1 │───▶│ pipe │───▶│cmd2 │───▶│ file2   │
│(input)  │    │     │    │      │    │     │    │(output) │
└─────────┘    └─────┘    └──────┘    └─────┘    └─────────┘
     ▲           ▲                                    ▲
     │           │                                    │
Child Process  Child Process                    Parent Process
```

### Extended Architecture (Bonus)
```
┌─────────┐    ┌─────┐    ┌──────┐    ┌─────┐    ┌──────┐    ┌─────┐    ┌─────────┐
│ file1   │───▶│cmd1 │───▶│pipe1 │───▶│cmd2 │───▶│pipe2 │───▶│cmd3 │───▶│ file2   │
│(input)  │    │     │    │      │    │     │    │      │    │     │    │(output) │
└─────────┘    └─────┘    └──────┘    └─────┘    └──────┘    └─────┘    └─────────┘
     ▲           ▲                       ▲                       ▲
     │           │                       │                       │
Child Process  Child Process         Child Process         Child Process
```

## System Calls Used

- `pipe()` - Creates communication channels between processes
- `fork()` - Creates child processes
- `dup2()` - Redirects file descriptors
- `execve()` - Replaces process with executable
- `open()` - Opens files
- `close()` - Closes file descriptors
- `waitpid()` - Waits for child processes to complete

## Process Flow

### Mandatory Version
1. **Setup**: Parse arguments and validate files
2. **Path Resolution**: Find executable paths in environment PATH
3. **Pipe Creation**: Create single pipe for inter-process communication
4. **Fork**: Create two child processes
5. **First Child**: Redirects stdin→file1, stdout→pipe, executes cmd1
6. **Second Child**: Redirects stdin→pipe, stdout→file2, executes cmd2

### Bonus Version
1. **Setup**: Parse arguments for multiple commands
2. **Path Resolution**: Find all executable paths
3. **Pipe Creation**: Create (n-1) pipes for n commands
4. **Fork Loop**: Create n child processes
5. **Child Processes**: Each handles specific position in pipeline
   - First child: stdin→file1, stdout→pipe[0]
   - Middle children: stdin→pipe[i-1], stdout→pipe[i]
   - Last child: stdin→pipe[n-2], stdout→file2

## Project Structure

```
pipex/
├── src/
│   ├── main.c              # Mandatory: Argument parsing, path resolution
│   └── pipex.c            # Mandatory: Core pipe implementation
├── bonus/
│   ├── src/
│   │   ├── main_bonus.c   # Bonus: Multiple command handling
│   │   └── pipex_bonus.c  # Bonus: Extended pipe implementation
│   ├── utils/
│   │   ├── init_struct_bonus.c  # Command parsing and initialization
│   │   ├── ft_free_bonus.c      # Memory management
│   │   └── [utility functions]
│   └── includes/
│       └── pipex_bonus.h  # Bonus header file
├── utils/
│   ├── ft_free.c          # Memory management
│   ├── ft_split.c         # String splitting
│   ├── ft_strlen.c        # String length
│   ├── ft_strdup.c        # String duplication
│   ├── ft_strjoin.c       # String concatenation
│   ├── ft_strncmp.c       # String comparison
│   └── ft_substr.c        # Substring extraction
├── includes/
│   └── pipex.h           # Main header file
├── ft_printf/            # Custom printf library
└── Makefile             # Build configuration
```

## Compilation

The project uses a Makefile with the following targets:

- `make` - Builds the mandatory executable
- `make bonus` - Builds the bonus executable with multiple command support
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
- Command not found errors (continues pipeline execution)
- Pipe creation failures
- Fork failures
- File descriptor errors
- Memory allocation failures

## Memory Management

- All dynamically allocated memory is properly freed
- No memory leaks in main process (verified with Valgrind)
- Proper cleanup on program termination
- Dynamic pipe allocation for bonus version

## Key Differences: Mandatory vs Bonus

| Feature | Mandatory | Bonus |
|---------|-----------|-------|
| Commands | Exactly 2 | Unlimited (≥2) |
| Pipes | 1 pipe | n-1 pipes for n commands |
| Processes | 2 children + 1 parent | n children + 1 parent |
| Memory | Static allocation | Dynamic pipe allocation |
| Error Handling | Basic | Enhanced with graceful degradation |

## Academic Project

This project is part of the 42 School curriculum, focusing on:

- Unix system programming
- Process management
- Inter-process communication
- File descriptor manipulation
- Error handling in C
- Memory management
- Dynamic allocation strategies

## Author

samalves - 42 Berlin

## License

This project is part of 42 School curriculum and follows their academic guidelines.
