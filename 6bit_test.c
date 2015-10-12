#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdecsix.c"

void print_hex(char *str, int len)
{
  for(int i = 0; i < len; i++) printf("%x", (unsigned char) str[i]);
  printf("\n");
}

int main()
{
  char *my_str = "HELLO! THIS IS A TEST OF MY ENCODING";
  int my_str_len = strlen(my_str);

  char *my_encoded = (char *)malloc(est_6mem_for_8str(my_str_len));
  int my_encoded_len;
  char *my_decoded = (char *)malloc(my_str_len + 1);
  int my_decoded_len;

  printf("Orig: %s\n", my_str);
  printf("Orig Len: %d\n", my_str_len);
  print_hex(my_str, my_str_len);

  conv_8str_to_6str(my_str, my_str_len, my_encoded, &my_encoded_len);

  printf("\n");
  printf("Enc Len: %d\n", my_encoded_len);
  print_hex(my_encoded, my_encoded_len);

  conv_6str_to_8str(my_encoded, my_encoded_len, my_decoded, &my_decoded_len);

  printf("\n");
  printf("Decoded: %s\n", my_decoded);
  printf("Dec Len: %d\n", my_decoded_len);
  print_hex(my_decoded, my_decoded_len);

  return 0;
}
