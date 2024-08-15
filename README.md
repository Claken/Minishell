# 🖥️ Minishell

Minishell is a simpler version of the command-line interpreter called shell.

A shell is a computer program (software) that exposes an operating system's services to a human user or other program.

## 👩🏻‍🏫 What I gained from the project
- I learned how to work on a big project in pairs.
- I've gained a deeper understanding of the concept of [process](https://en.wikipedia.org/wiki/Process_(computing))
- I learned to use [fork](https://www.geeksforgeeks.org/fork-system-call/) to handle parent and child processes.
- I learned how to handle [signals](https://en.wikipedia.org/wiki/Signal_(IPC)).
- I learned to use [pipes](https://www.geeksforgeeks.org/pipe-system-call/) to communicate with different processes.

## 📦 Prerequisites

You need to install clang if you don't have it :
```
sudo apt install clang
```
You also need to install 'readline/readline.h' if it turns out that the file is missing :
```
sudo apt-get install libreadline-dev
```

## 🚀 Usage

type this command at the root of the project :
```
make
```
You will have an executable called "minishell". <br/>

Launch the program with this command :
```
./minishell
```
