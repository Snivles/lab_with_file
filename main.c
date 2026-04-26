#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ConvertToSmall(FILE *text)
{
  if (text!=NULL){

  char el;
  unsigned buf1[8];
  int count = 0;

  unsigned char result;

  while (fscanf(text,"%c",&el)!= -1)
  {
    buf1[count] = el;
    count++;
    if(count == 8){
      int i = 0;
      while (i < 7){
        result = (buf1[i+1] | ( (buf1[0] >> i)&1 )<<7);
        printf("%c",result);
        i++;
        }
      count = 0;
      }
}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      printf("%c",buf1[i]);}}}
}

void ConvertSMallto(unsigned char*text)
// {
//   if (text==NULL){return NULL;}

//   int dlina = 0;
//   while (text[dlina] != '\0')
//         {dlina += 1;}
//   int block = dlina / 7;



//   unsigned char *result = (unsigned char*)malloc((dlina + block) + 1); // выделяю память под результирующую строку
//   int count = 0;
//   size_t newc = 0;
//   int blocks = 0;
//   unsigned char maska = 0;
//   unsigned char mask = 0;
//   mask = (mask << 7);
//   while (blocks < block)
//   {
//     maska = 0;
//     int i = 0;
//     while (i < 7){
//           maska = maska | ((text[count+i]>>7)&1) << i;
//           i++;}
//     result[newc] = maska;
//     newc++;

//     i = 0;
//     while(i < 7){
//       result[newc] = (text[count]& ~mask);
//       newc++;
//       i++;}
//     count += 7;
//     blocks += 1;
// }


//   while (count < dlina){
//     result[newc] = text[count];
//     count++;
//     newc++;}

//   result[newc] = '\0';
//   return result;
// }






int main()
{

  FILE*ptr = NULL;
  FILE*ptr2 = NULL;
  ptr= fopen("first.txt","rb");
  ptr2 = fopen("second.txt","wb");
  if (ptr == NULL){return 0;}

  ConvertToSmall(ptr);



  fclose(ptr);
  return 0;
}
