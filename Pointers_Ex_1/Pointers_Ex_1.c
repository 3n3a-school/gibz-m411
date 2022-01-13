// Pointers_Ex_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int number;
  printf("Enter a number: ");
  scanf_s("%d", &number);
  unsigned char * num_char = (unsigned char*)&number;
  printf("Number %d in hex format %X\n", number, *num_char);
  while (*num_char != '\0') {
    printf("Ausgabe %02X\n", *num_char++);
  }
}