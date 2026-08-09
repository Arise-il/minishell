# minishell

`minishell` is a project from the **1337 cursus** focused on building a functional **UNIX shell** in C.

The goal of the project is to recreate the core behavior of a shell such as `bash`, while implementing process creation, command execution, pipes, redirections, environment variables, signals, and built-in commands.

The project provides a deeper understanding of how shells work internally and how UNIX processes communicate with each other.

---

## Table of Contents

* [Overview](#overview)
* [Features](#features)
* [Compilation](#compilation)
* [Usage](#usage)
* [Shell Prompt](#shell-prompt)
* [Command Execution](#command-execution)
* [Built-in Commands](#built-in-commands)
* [Redirections](#redirections)
* [Pipes](#pipes)
* [Environment Variables](#environment-variables)
* [Exit Status](#exit-status)
* [Signals](#signals)
* [Parsing](#parsing)
* [Process Management](#process-management)
* [Memory Management](#memory-management)
* [Project Structure](#project-structure)
* [Testing](#testing)
* [1337 Project](#1337-project)

---

# Overview

`minishell` is a simplified implementation of a UNIX shell.

When launched, it displays a prompt and waits for commands:

```text
$ ./minishell
minishell$
```

The user can then enter commands such as:

```bash
ls
pwd
echo Hello
cd ..
```

The shell parses the input, handles special shell syntax, creates the required processes, and executes the requested commands.

The general execution flow is:

```text
User Input
    │
    ▼
  Lexer
    │
    ▼
  Parser
    │
    ▼
Command Structure
    │
    ▼
Redirections / Pipes
    │
    ▼
Process Creation
    │
    ▼
Command Execution
    │
    ▼
Exit Status
```

---

# Features

The mandatory implementation supports:

* Interactive shell prompt
* Command execution
* Absolute and relative paths
* `PATH` command lookup
* Environment variables
* Variable expansion
* Single quotes
* Double quotes
* Input redirection `<`
* Output redirection `>`
* Append redirection `>>`
* Here-document `<<`
* Pipes `|`
* Built-in commands
* `$?` exit status
* Signal handling
* Process management
* Error handling
* Proper memory management
* `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` behavior

---

# Compilation

Compile the project using:

```bash
make
```

This creates the `minishell` executable.

### Remove object files

```bash
make clean
```

### Remove object files and executable

```bash
make fclean
```

### Recompile the project

```bash
make re
```

---

# Usage

Start the shell with:

```bash
./minishell
```

You should see a prompt similar to:

```text
minishell$
```

You can then enter commands normally:

```bash
minishell$ ls
minishell$ pwd
minishell$ echo Hello
```

To exit:

```bash
minishell$ exit
```

You can also use:

```text
Ctrl-D
```

on an empty prompt.

---

# Shell Prompt

The shell continuously performs the following cycle:

```text
Display prompt
      ↓
Read input
      ↓
Parse input
      ↓
Execute command
      ↓
Wait for processes
      ↓
Display prompt again
```

This continues until the user exits the shell or sends an EOF with `Ctrl-D`.

---

# Command Execution

External commands are executed by creating a new process.

For example:

```bash
ls -la
```

The shell:

1. Parses the command.
2. Searches for the executable.
3. Creates a child process using `fork()`.
4. Configures redirections and pipes if necessary.
5. Executes the command using `execve()`.
6. The parent waits for the child.
7. The exit status is stored.

The general process flow is:

```text
             minishell
                 │
               fork()
              /      \
             /        \
        Parent        Child
          │             │
        wait()       execve()
                        │
                        ▼
                    Command
```

---

# Built-in Commands

The mandatory project implements the required shell built-ins.

## `echo`

Prints text to the terminal.

```bash
echo Hello World
```

Output:

```text
Hello World
```

The `-n` option is supported:

```bash
echo -n Hello
```

---

## `cd`

Changes the current working directory.

```bash
cd ..
```

Examples:

```bash
cd /tmp
cd ..
cd ~
```

The shell updates the relevant environment variables when the directory changes.

---

## `pwd`

Displays the current working directory.

```bash
pwd
```

Example:

```text
/home/user/minishell
```

---

## `export`

Creates or modifies environment variables.

```bash
export NAME="Ilyas"
```

Then:

```bash
echo $NAME
```

produces:

```text
Ilyas
```

---

## `unset`

Removes an environment variable.

```bash
unset NAME
```

Afterwards:

```bash
echo $NAME
```

produces an empty value.

---

## `env`

Displays the current environment variables.

```bash
env
```

---

## `exit`

Terminates the shell.

```bash
exit
```

The built-in also supports an exit status:

```bash
exit 42
```

---

# Redirections

The shell supports the required UNIX redirections.

## Input Redirection `<`

Redirects standard input from a file.

```bash
cat < file.txt
```

Instead of reading from the terminal, `cat` reads from `file.txt`.

---

## Output Redirection `>`

Redirects standard output to a file.

```bash
echo Hello > output.txt
```

The file is created or overwritten.

---

## Append Redirection `>>`

Appends output to a file.

```bash
echo Hello >> output.txt
```

Existing content is preserved.

---

## Here-document `<<`

Reads input until a specified delimiter is encountered.

Example:

```bash
cat << EOF
Hello
World
EOF
```

The shell provides the entered text to the command as standard input.

---

# Pipes

The pipe operator `|` connects the output of one command to the input of another.

Example:

```bash
ls | grep minishell
```

The execution flow is:

```text
┌─────────┐       pipe       ┌─────────┐
│   ls    │ ────────────────> │  grep   │
└─────────┘                   └─────────┘
 stdout                         stdin
```

Multiple pipes are supported:

```bash
cat file.txt | grep hello | wc -l
```

Each command runs in its own process and communicates through pipes.

---

# Environment Variables

The shell maintains its own environment.

Variables can be accessed using `$`:

```bash
echo $HOME
```

Other examples:

```bash
echo $PATH
echo $USER
echo $PWD
```

---

## Variable Expansion

The shell expands environment variables before executing a command.

For example:

```bash
export NAME="World"
echo Hello $NAME
```

produces:

```text
Hello World
```

The special variable `$?` contains the exit status of the previous command.

Example:

```bash
false
echo $?
```

Output:

```text
1
```

---

# Quotes

The shell supports both single and double quotes.

## Single Quotes

Everything inside single quotes is treated literally.

```bash
echo '$HOME'
```

The output is:

```text
$HOME
```

---

## Double Quotes

Variables can be expanded inside double quotes.

```bash
echo "$HOME"
```

The value of `$HOME` is expanded.

---

# Exit Status

Every command returns an exit status.

The status can be accessed using:

```bash
$?
```

For example:

```bash
ls
echo $?
```

A successful command normally returns:

```text
0
```

A failed command generally returns a non-zero value.

---

# Signals

Signal handling is an important part of `minishell`.

The shell handles the following keyboard signals.

## `Ctrl-C`

Sends `SIGINT`.

At the prompt, it should interrupt the current input and display a new prompt.

```text
^C
minishell$
```

---

## `Ctrl-D`

Sends EOF when the input is empty.

It exits the shell.

```text
minishell$ exit
```

---

## `Ctrl-\`

Sends `SIGQUIT`.

Its behavior depends on whether the shell is currently waiting for a command or running a child process.

The shell must reproduce the expected behavior of a standard shell as closely as required by the project.

---

# Parsing

The input must be parsed before execution.

For example:

```bash
cat < input.txt | grep "hello" > output.txt
```

contains several different elements:

```text
Command
   │
   ├── redirection <
   │
   ├── pipe |
   │
   ├── quotes
   │
   └── redirection >
```

The parser transforms the raw input into an internal command representation that the executor can process.

A typical parsing flow is:

```text
Input
  ↓
Tokenization
  ↓
Quote Handling
  ↓
Variable Expansion
  ↓
Syntax Validation
  ↓
Command Structures
  ↓
Execution
```

---

# Process Management

External commands require process creation.

The shell uses:

```c
fork()
execve()
wait()
waitpid()
```

### `fork()`

Creates a child process.

### `execve()`

Replaces the child process with the requested program.

### `wait()` / `waitpid()`

Allows the parent shell to wait for child processes and retrieve their exit status.

---

# File Descriptors

Redirections and pipes rely heavily on file descriptors.

The standard descriptors are:

```text
0 → stdin
1 → stdout
2 → stderr
```

For example:

```bash
echo Hello > output.txt
```

the shell redirects:

```text
stdout (1)
     │
     ▼
output.txt
```

Pipes also work by replacing the standard input/output descriptors of processes.

---

# Memory Management

`minishell` performs a significant amount of dynamic memory allocation.

Memory must be properly managed for:

* Tokens
* Command structures
* Environment arrays
* Expanded strings
* Parsed arguments
* Redirection structures
* Pipes
* Temporary buffers

The project should be checked for memory leaks using tools such as:

```bash
valgrind --leak-check=full ./minishell
```

The shell should also correctly clean up resources when:

* A command fails.
* A redirection fails.
* A pipe fails.
* A child process terminates.
* The shell exits.

---

# Testing

`minishell` should be tested against standard shell behavior.

Basic commands:

```bash
echo hello
pwd
ls
env
```

Built-ins:

```bash
cd ..
export TEST=hello
echo $TEST
unset TEST
exit
```

Redirections:

```bash
echo hello > file
cat < file
echo world >> file
cat file
```

Pipes:

```bash
ls | grep minishell
cat file | grep hello | wc -l
```

Quotes:

```bash
echo 'hello world'
echo "hello $USER"
```

Exit status:

```bash
false
echo $?
```

Here-document:

```bash
cat << EOF
Hello
World
EOF
```

Signals:

```text
Ctrl-C
Ctrl-D
Ctrl-\
```

---

# Comparison with Bash

A useful way to test `minishell` is to execute the same commands in both:

```bash
bash
```

and:

```bash
./minishell
```

Then compare:

* Command output
* Exit statuses
* Redirections
* Pipes
* Quotes
* Environment variables
* Signal behavior
* Error messages
* Built-in behavior

The objective is to reproduce the required behavior of a standard shell as closely as possible.

---

# Makefile

The Makefile provides the standard targets:

```bash
make
make clean
make fclean
make re
```

### `make`

Builds the `minishell` executable.

### `make clean`

Removes object files.

### `make fclean`

Removes object files and the executable.

### `make re`

Cleans and recompiles the project.

---

# 1337 Project

**Project:** minishell
**School:** 1337
**Language:** C
**Category:** UNIX / Processes / Shell / IPC

The project focuses on:

* Process creation
* `fork()`
* `execve()`
* `wait()` / `waitpid()`
* Pipes
* File descriptors
* Redirections
* Signals
* Environment variables
* Parsing
* Command execution
* Built-in commands
* Memory management

---

# Final Goal

The main objective of `minishell` is to understand how a UNIX shell works internally and how it interacts with the operating system.

The project combines:

```text
Parsing
   +
Process Management
   +
File Descriptors
   +
Pipes
   +
Redirections
   +
Signals
   +
Environment Variables
   +
C Programming
```

into a functional command-line shell.

