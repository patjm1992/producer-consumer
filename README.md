# producer-consumer 

A deadlock-free implementation of the [producer-consumer](https://en.wikipedia.org/wiki/Producer-consumer_problem) problem that uses semaphores.

1 producer, 1 consumer:

![alt-text](https://github.com/patjm1992/producer-consumer/raw/master/gifs/1p1c.gif)

100 producers, 1 consumers:

![alt-text](https://github.com/patjm1992/producer-consumer/raw/master/gifs/100p1c.gif)

Usage
-----

```
$ producerconsumer *num_producers* *num_consumers*
```