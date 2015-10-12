/* DEC SIX Encoding */
char* six_bit_conv =
  " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_";

int find_6val(char x)
{
  for(int i = 0; i < 64; i++)
  {
    if (six_bit_conv[i] == x)
    {
      return i;
    }
  }
  return -1;
}

int find_8val(char x)
{
  if (x < 64)
  {
    return six_bit_conv[x];
  }
  return -1;
}

/*
 * Using 32-bit bit-arithmetic could probably improve this
 */
void conv_8str_to_6str(char* str8, int str8_len, char* str6, int* str6_len)
{
  int bits_left = 0;
  int byte_at = 0;
  for(int i = 0; i < str8_len; i++)
  {
    unsigned char b1 = find_6val(str8[i]);
    switch(bits_left)
    {
      case 0:
        str6[byte_at] = b1 << 2;
        bits_left = 2;
        break;
      case 2:
        str6[byte_at]     = str6[byte_at] | b1 >> 4;
        str6[byte_at + 1] = str6[byte_at + 1] | b1 << 4;
        bits_left = 4;
        byte_at = byte_at + 1; 
        break;
      case 4:
        str6[byte_at]     = str6[byte_at] | b1 >> 2 ;
        str6[byte_at + 1] = str6[byte_at + 1] | b1 << 6;
        bits_left = 6;
        byte_at = byte_at + 1; 
        break;
      case 6:
        str6[byte_at]     = str6[byte_at] | (b1);
        bits_left = 0;
        byte_at = byte_at + 1; 
        break;
    }
  }
  *str6_len = byte_at + 1;
}

void conv_6str_to_8str(char* str6, int str6_len, char* str8, int* str8_len)
{
  int bits_left = 0;
  int byte_at = 0;

  unsigned char x, y;
  for(int i = 0; i < str6_len; byte_at++, i++)
  {
    switch(bits_left)
    {
      case 0:
        y = str6[i];
        str8[byte_at] = find_8val(y >> 2);
        bits_left = 2;
        break;
      case 2:
        x = str6[i-1];
        y = str6[i];
        str8[byte_at] = find_8val(0x3f & ( (x << 4) | (y >> 4) ) );
        bits_left = 4;
        break;
      case 4:
        x = str6[i-1];
        y = str6[i];
        str8[byte_at] = find_8val(0x3f & ( (x << 2) | (y >> 6) ) );

        byte_at += 1;
        str8[byte_at] = find_8val(0x3f & y);
        bits_left = 0;
        break;
    }
  }
  *str8_len = byte_at;
}

int est_6mem_for_8str(int len)
{
  return 1 + (int) ( 0.75 * len);
}

int est_8mem_for_6str(int len)
{
  return 1 + (int) ( 4.0/3.0 * len);
}
