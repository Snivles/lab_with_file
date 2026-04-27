#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//тест для first.txt - 15 Байт : second.txt 14-Байт , после обратного получаем 15 (те же самые)
//тест для first.txt - 26 Байт : second.txt 23-Байт , после обратного получаем 26 (те же самые)
//тест для first.txt - 0 Байт : second.txt 0-Байт , после обратного получаем 0 (те же самые)
void Encryption(FILE *readthis , FILE*writein)
{
  if (readthis!=NULL && writein != NULL){

  char el;
  unsigned char buf1[8];
  int count = 0;

  unsigned char result;

  while (fscanf(readthis,"%c",&el)!= -1)
  {
    buf1[count] = el;
    if(buf1[count] > 128){break;}
    count++;
    if(count == 8){
      int i = 0;
      while (i < 7){
        result = (buf1[i+1] | ( (buf1[0] >> i)&1 )<<7);
        fprintf(writein, "%c",result);
        i++;
        }
      count = 0;
      }
}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      fprintf(writein, "%c",buf1[i]);
}}}}





void Dencryption(FILE *readthis , FILE*writein){ // текст это файл ЗАшифрованный 2 это файл куда писать расшифровку
if (readthis!=NULL && writein != NULL){
  char el;
  unsigned char buf1[7];
  int count = 0;
  unsigned char mask = 1;


  while (fscanf(readthis,"%c",&el)!= -1){
      buf1[count] = el;
      count++;
      if (count == 7){
          unsigned char res[8] = {0};
          int i = 0;
          while (i < 7){
                res[0] = res[0] | ((buf1[i] >> 7) & 1) << i;
                i++;}
          i = 0;
          while (i < 7){
                res[i+1] = buf1[i] & ~(mask << 7);
                i++;}
          for(i = 0; i < 8; i++){
                if (i == 0 && res[i] == 0){continue;}
                fprintf(writein,"%c",res[i]);}
          count = 0;
        }
    }

  if (count  > 0){
    for(int i=0 ; i < count; i++){
      fprintf(writein, "%c",buf1[i]);
}}}}

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

  Encryption(ptr,ptr2);
  fclose(ptr);
  fclose(ptr2);}

  ptr= fopen("second.txt","r");
  ptr2 = fopen("first.txt","w");
  if (ptr != NULL && ptr2 != NULL){

  Dencryption(ptr,ptr2);
  fclose(ptr);
  fclose(ptr2);}
  return 0;
}
