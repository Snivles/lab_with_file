#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned char *ConvertToSmall(unsigned char*text)
{
  if (text==NULL){return NULL;}

  int dlina = 0;
  while (text[dlina] != '\0')
        {dlina += 1;}

  unsigned char *result = (unsigned char*)malloc(dlina + 1); // выделяю память под результирующую строку
  int count = 0;
  size_t newc = 0;
  int block = dlina / 8;
  int blocks = 0;
  unsigned char simvol = 0;
  int maska=7 ;
  while (blocks < block)
  {
    simvol = text[count];

    int i = 0;
    while (i < 7){
      result[newc] = (text[count+i+1] | ( (simvol >> (7 - maska))&1 )<<7);
      newc++;
      maska--;
      i++;
      }

    count += 8;
    blocks += 1;
    }


  while (count < dlina){
    result[newc] = text[count];
    count++;
    newc++;}


  result[newc] = '\0';
  return result;
}

unsigned char *ConvertSMallto(unsigned char*text)
{
  if (text==NULL){return NULL;}

  int dlina = 0;
  while (text[dlina] != '\0')
        {dlina += 1;}
  int block = dlina / 7;



  unsigned char *result = (unsigned char*)malloc((dlina + block) + 1); // выделяю память под результирующую строку
  int count = 0;
  size_t newc = 0;
  int blocks = 0;
  unsigned char maska = 0;
  unsigned char mask = 0;
  mask = (mask << 7);
  while (blocks < block)
  {
    maska = 0;
    int i = 0;
    while (i < 7){
          maska = maska | ((text[count+i]>>7)&1) << i;
          i++;}
    result[newc] = maska;
    newc++;

    i = 0;
    while(i < 7){
      result[newc] = (text[count]& ~mask);
      newc++;
      i++;}
    count += 7;
    blocks += 1;
}


  while (count < dlina){
    result[newc] = text[count];
    count++;
    newc++;}

  result[newc] = '\0';
  return result;
}






int main()
{

  FILE*ptrFile = NULL;
  FILE *ptrCopyF = NULL;
  char el;
  ptrFile = fopen("first.txt","rb");
  if (ptrFile == NULL){return 0;}



  unsigned char text[1000] = "zaaaaaaaffff";
  unsigned char *ptr = ConvertToSmall(text);
  int i =0;
  while (ptr[i] != '\0'){
    printf("%c",ptr[i]);
    printf("\n");
    i++;}
  i =0;
  printf("\n");
  unsigned char *ptr2 = ConvertSMallto(ptr);
  while (ptr2[i] != '\0'){
    printf("%c",ptr2[i]);
    printf("\n");
    i++;}
  fclose(ptrFile);
  free(ptr);
  free(ptr2);
  return 0;
}
