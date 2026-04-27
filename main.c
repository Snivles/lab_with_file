#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//тест для first.txt - 15 Байт : second.txt 14-Байт , после обратного получаем 15 (те же самые)
//тест для first.txt - 26 Байт : second.txt 23-Байт , после обратного получаем 26 (те же самые)
//тест для first.txt - 0 Байт : second.txt 0-Байт , после обратного получаем 0 (те же самые)
//тест для Abstract. The present paper upholds the problem of quoting as a form of dialogism in postmodern text. Methodologically, the approach, proposed by the authors, integrates two theories. Firstly, it draws on Van Dijk
// 213 Б , в зашифрованном варианте 187 Б (верное шифрование)
// asdasdsadП - 11 байт(10 байт для латиницы и +1 для кириллицы) на выходе зашифрованный код имеет 8 байт а дешиф 9 байт( дошли до П и стоп)
bool Compress(char * readthis , char*writein)
{
  FILE*in = fopen(readthis,"r");
  FILE*out = fopen(writein,"w");
  if (readthis==NULL || writein == NULL){return false;}

  char el;
  unsigned char buf1[8];
  int count = 0;

  unsigned char result;

  while (fscanf(in,"%c",&el)!= -1)
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
        fprintf(out, "%c",result);
        i++;
        }
      count = 0;
      }
}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      fprintf(in, "%c",buf1[i]);

  }
}
return true;}





bool DeCompress(char *readthis , char*writein){ // текст это файл ЗАшифрованный 2 это файл куда писать расшифровку
  FILE *in= fopen(readthis,"r");
  FILE*out  = fopen(writein,"w");
if (readthis==NULL || writein == NULL){ return false;}
  char el;
  unsigned char buf1[7];
  int count = 0;
  unsigned char mask = 1;


  while (fscanf(in,"%c",&el)!= -1){
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
                fprintf(out,"%c",res[i]);}
          count = 0;
        }
    }

  if (count  > 0){
    for(int i=0 ; i < count; i++){
      fprintf(in, "%c",buf1[i]);
}}

return true;}







int main()
{

  char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/first.txt");
  char ptr2[1000] = ("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/second.txt");
  if(Compress(ptr,ptr2)){
    printf("Correct Encryption");
}
  else{printf("Wrong Encryption");
      return 0;}
  fclose(ptr);
  fclose(ptr2);}
  else{printf("ERROR WITH NULL"); return 0;}
  printf("\n");


  if (ptr != NULL && ptr2 != NULL){

  if (DeCompress(ptr,ptr2)){
    printf("Correct Dencryption");
}
  else{printf("Wrong Dencryption");
      fclose(ptr);
      fclose(ptr2);
      return 0;}

  fclose(ptr);
  fclose(ptr2);}
  else{printf("ERROR WITH NULL"); return 0;}}

