#include <stdio.h>
#include <unistd.h>

void main()
{
  execl("./server", "");	/* Just start the server here! */
}
