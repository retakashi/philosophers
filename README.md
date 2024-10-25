# philosophers
![gif](https://github.com/retakashi/philo/blob/main/philo/philo.gif)

## Overview
Implementation of the dining philosophers problem with mutexes.

## Implementation Environment

- **Programming Language**: C
- **Operating Systems**: macOS
- **Compiler**: Apple Clang 15.0.0 (clang-1500.3.9.4), Target: arm64-apple-darwin23.6.0

## Usage
``` bash
git clone ...
cd philosophers
cd philo
make
./philo <number of philosophers> <time to die> <time to eat> <time to sleep> [number of times each philosopher must eat]
```
The unit of time is milliseconds.

## Reference
[philosophers-visualizer](https://github.com/nafuka11/philosophers-visualizer)
