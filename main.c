#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//тест для first.txt - 15 Байт : second.txt 14-Байт , после обратного получаем 15 (те же самые)
//тест для first.txt - 26 Байт : second.txt 23-Байт , после обратного получаем 26 (те же самые)
//тест для first.txt - 0 Байт : second.txt 0-Байт , после обратного получаем 0 (те же самые)
//тест для Abstract. The present paper upholds the problem of quoting as a form of dialogism in postmodern text. Methodologically, the approach, proposed by the authors, integrates two theories. Firstly, it draws on Van Dijk
// 213 Б , в зашифрованном варианте 187 Б (верное шифрование)
// asdasdsadП - 11 байт(10 байт для латиницы и +1 для кириллицы) на выходе зашифрованный код имеет 8 байт а дешиф 9 байт( дошли до П и стоп)
int Encryption(FILE *readthis , FILE*writein)
{
  if (readthis!=NULL && writein != NULL){

  char el;
  unsigned char buf1[8];
  int count = 0;

  unsigned char result;

  while (fscanf(readthis,"%c",&el)!= -1)
  {
    buf1[count] = el;
    if(buf1[count] >= 128){
      break;
}
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

  return count;}}}
return -1;
}





int Dencryption(FILE *readthis , FILE*writein){ // текст это файл ЗАшифрованный 2 это файл куда писать расшифровку
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
}}
  return count;}

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
  //ptr= fopen("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/first.txt","r");
  ptr2 = fopen("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/second.txt","w");
  if (ptr != NULL && ptr2 != NULL){

  if(Encryption(ptr,ptr2)>=0){
    printf("Correct encryption");
}
  else{printf("Wrong encryption");
      return 0;}
  fclose(ptr);
  fclose(ptr2);}
  else{printf("ERROR WITH NUKK"); return 0;}
  printf("\n");
  ptr= fopen("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/second.txt","r");
  ptr2 = fopen("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/first.txt","w");
  if (ptr != NULL && ptr2 != NULL){

  if (Dencryption(ptr,ptr2) >=0){
    printf("Correct Dencryption");
}
  else{printf("Wrong Dencryption");
      return 0;}

  fclose(ptr);
  fclose(ptr2);}
  printf("ERROR WITH NUKK"); return 0;
  return 0;}

