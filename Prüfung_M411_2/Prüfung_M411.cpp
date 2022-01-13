#include <stdio.h>
#include <Windows.h>

void ConvertDecimal2Binary(unsigned long dec, unsigned char bin[], unsigned char* pLength);

int main()
{
  // Decimal 2 Binary
  // Enea K. 2021

  unsigned long num;
  unsigned char binary_num[64];
  unsigned char len = 3;

  printf("Dieses Programm konvertiert eine Dezimalzahl in die Dualzahl ...\n");
  printf("Geben Sie eine positive Dezimalzahl ein >");
  scanf_s("%d", &num);

  ConvertDecimal2Binary(num, binary_num, &len);

  printf("Die Dualzahl>");
  int padding = 0;
  for (int j = len - 1; j >= 0; j--) {
    if (padding == 7) {
      printf("%d ", binary_num[j]);
      padding = 0;
    }
    else {
      printf("%d", binary_num[j]);
      padding++;
    }

  }
  printf("\n");
  system("pause");
}

void ConvertDecimal2Binary(unsigned long dec, unsigned char bin[], unsigned char* pLength) {
  int i = 0;
  while (dec > 0)
  {
    bin[i] = dec % 2;
    dec = dec / 2;
    i++;
  }
  *pLength = i;
};