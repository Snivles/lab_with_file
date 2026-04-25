#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned char *ConvertToSmall(unsigned char*text)
{
  if (text==NULL){return NULL;}

  size_t dlina = 0;
  while (text[dlina] != '\0')
        {dlina += 1;}


  unsigned char *result = (unsigned char*)malloc(dlina + 1); // выделяю память под результирующую строку
  int count = 0;
  size_t newc = 0;
  int ostatok = dlina%8;
  int block = dlina / 8;
  unsigned char simvol = 0;
  while (count < block*8)
  {
    if (count%8==0){
          simvol = text[count];}

    else{
      result[newc] = (text[count] | ( (simvol >> (7 - (count%8)))&1 )<<7);
      newc++;

      }

    count++;
    }
  if (ostatok!= 0){
    for (int i = 0; i<ostatok;i++){
        result[newc]= text[block * 8 + i];
        newc++;}

}
  result[newc] = '\0';
  return result;
}




unsigned char *ConvertSMallto(unsigned char*text)
{
  if (text==NULL){return NULL;}

  size_t dlina = 0;
  while (text[dlina] != '\0')
        {dlina += 1;}
  int block = dlina / 7;
//8 8 8 4 = 28
//7 7 7 4 = 25
  unsigned char *result = (unsigned char*)malloc((dlina + block) + 1); // выделяю память под результирующую строку
  int count = 0;
  size_t newc = 0;
  unsigned char simvol = 0;
  while (count < block*8)
  {
    if (count%8==0){
          simvol = text[count];}

    else{
      result[newc] = (text[count] | ( (simvol >> (7 - (count%8)))&1 )<<7);
      newc++;

      }

    count++;
    }
  int ostatok = (dlina+block)-(block*7);
  if (ostatok!= 0){
    for (int i = 0; i<ostatok;i++){
        result[newc]= text[block * 8 + i];
        newc++;}

}
  result[newc] = '\0';
  return result;
}






int main()
{
  unsigned char text[1000] = "zaaaaaaaffffffff";
  unsigned char *ptr = text;
  ptr = ConvertToSmall(ptr);
  int i =0;
  while (ptr[i] != '\0'){
    printf("%c",ptr[i]);
    i++;
}

  return 0;
}
