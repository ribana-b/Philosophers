# Philosophers

## Preview

[preview.webm](https://github.com/user-attachments/assets/87875fd2-f2a1-4f01-bacd-0752b7c0ce98)

## Description

Philosophers ([Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)) is a project where the goal is to let n amount of philosophers eat indefinitely without dying. Each philosopher must take forks to be able to eat, then sleep, and then think whenever they're not eating nor sleeping. By achieving the goal, we adquire knowledge about concurrency problems such as deadlocks and data races and how to deal with them.

## Usage

Clone the repository and build the program
```bash
git clone https://github.com/ribana-b/philosophers
cd philosophers/philo
make -j4
```

Run the program

```bash
./philo 10 800 200 200 2
```

> [!NOTE]
> |Parameter|Value range|
> |-|-|
> |number of philosophers|1-200|
> |time to die|60-999999|
> |time to eat|60-999999|
> |time to sleep|60-999999|
> |number of meals per philosopher (optional)|0-999999|

## Progress

If you are interested in checking my progress in 42 Common Core, I suggest you to take a look at [My Common Core Projects](https://github.com/ribana-b/#common-core)
