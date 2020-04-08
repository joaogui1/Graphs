all: graph.h graph.c hash.h hash.c graphsim.c
  gcc -o exe graph.c main.c -std=c99

run:
  ./exe