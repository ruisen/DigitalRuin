/****************************************************************
 * File Name: controller.c
 * Create Time: Sun Aug 25 12:31:13 2013
 * Author: Ruisen Luo
 * Description: 
 ****************************************************************/

#include <stdio.h>
#include <unistd.h>

void main()
{
  execl("./server", "");	/* Just start the server here! */
}
