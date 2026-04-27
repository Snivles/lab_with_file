#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ConvertToSmall(FILE *text , FILE*second)
{
  if (text!=NULL && second != NULL){

  char el;
  unsigned char buf1[8];
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
        fprintf(second, "%c",result);
        i++;
        }
      count = 0;
      }
}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      fprintf(second, "%c",buf1[i]);
}}}}





void ConverttoNorm(FILE *text , FILE*second){ // текст это файл ЗАшифрованный 2 это файл куда писать расшифровку
if (text!=NULL && second != NULL){
  char el;
  unsigned char buf1[7];
  int count = 0;
  unsigned char mask = 1;
  while (fscanf(text,"%c",&el)!= -1){
      buf1[count] = el;
      count++;
      if (count == 7){
          unsigned char res[8];
          int i = 0;
          while (i < 7){
                res[0] = res[0] | ((buf1[i] >> 7) & 1) << i;}
          i = 0;
          while (i < 7){
                res[i+1] = buf1[i] & ~(mask << 7);}
          for(i = 0; i < 8; i++){
                fprintf(second,"c",res[i]);}
      }
    }
  }
}
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
  ptr= fopen("first.txt","r");
  ptr2 = fopen("second.txt","w");
  if (ptr != NULL && ptr2 != NULL){

  ConvertToSmall(ptr,ptr2);

  ConverttoNorm(ptr2,ptr);
  fclose(ptr);
  fclose(ptr2);
  return 0;
}
}
