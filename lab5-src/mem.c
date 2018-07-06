
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE *fd, char * p , int len);

struct X{
  char a;
  int i;
  char b;
  int *p;
};

struct List {
  char * str;
  struct List * next;
};

int
main() {
  char str[20];
  double y = 14;
  int a = 66;
  int b = -77;
  struct X x;
  struct List * head;

  x.a = 'G';
  x.i = 42;
  x.b = '0';
  x.p = &x.i;
  strcpy(str, "Hello world\n");
  printf("&str=0x%lX\n", (unsigned long)str);
  printf("&x=0x%lX\n", (unsigned long)&x.a);
  printf("&y=0x%lX\n", (unsigned long) &y);

  mymemdump(stdout, (char *) &x.a, 64);
  head = (struct List *) malloc(sizeof(struct List));
  head->str=strdup("Greetings ");
  head->next = (struct List *) malloc(sizeof(struct List));
  head->next->str = strdup("from ");
  head->next->next = (struct List *) malloc(sizeof(struct List));
  head->next->next->str = strdup("cs250");
  head->next->next->next = NULL;
  printf("head=0x%lx\n", (long unsigned int)head);
  mymemdump(stdout, (char*) head, 256);
}

