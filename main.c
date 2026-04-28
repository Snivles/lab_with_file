#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//тест для first.txt - 15 элементов : second.txt 14-элементов , после обратного получаем 15 (те же самые)
//тест для first.txt - 26 Байт : second.txt 23-Байт , после обратного получаем 26 (те же самые)
//тест для first.txt - 0 Байт : second.txt 0-Байт , после обратного получаем 0 (те же самые)
//тест для Abstract. The present paper upholds the problem of quoting as a form of dialogism in postmodern text. Methodologically, the approach, proposed by the authors, integrates two theories. Firstly, it draws on Van Dijk
// 213 Б , в зашифрованном варианте 187 Б (верное шифрование)
// asdasdsadП - 11 байт(10 байт для латиницы и +1 для кириллицы) на выходе зашифрованный код имеет 8 байт а дешиф 9 байт( дошли до П и стоп)


//тест для first.txt - 7 элементов (aaaaaaa): second.txt 7-элементов , после обратного получаем 7(aaaaaaa)
//тест для first.txt - 8 элементов (aaaaaaaa): second.txt 7-элементов , после обратного получаем 8(aaaaaaa)
//тест для first.txt - 15 элементов (aaaaaaaaaaaaaa): second.txt 14-элементов , после обратного получаем 15(aaaaaaaaaaaaaa
//тест для first.txt - 16 элементов (aaaaaaaaaaaaaaa): second.txt 14-элементов , после обратного получаем 16(aaaaaaaaaaaaaaa)
//тест для first.txt - 15 элементов (aaaaaaaaaaaaaa): second.txt 14-элементов , после обратного получаем 15(aaaaaaaaaaaaaa)
//тест дя first.txt - 11 элементов (12 байт) (AbcdefgПasd): WRONG Compress
bool Compress(char * readthis , char*writein)
{
  FILE*in = fopen(readthis,"r");
  FILE*out = fopen(writein,"w");
  if (in==NULL || out == NULL){
      return false;}

  char el;
  unsigned char buf1[8];
  int count = 0;

  unsigned char result;

  while (fscanf(in,"%c",&el)!= -1)
  {
    buf1[count] = el;
    if(buf1[count] > 127){
        fclose(in);
        fclose(out);
        return false;}

    count++;
    if(count == 8){
      int i = 0;
      while (i < 7){
        result = (buf1[i+1] | ( (buf1[0] >> i)&1 )<<7);
        if(fprintf(out, "%c",result)<0){
            return false;}
        i++;
        }
      count = 0;
      }
}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      if((fprintf(out, "%c",buf1[i]))<0){
          return false;}

  }
}
  fclose(in);
  fclose(out);
return true;}





bool DeCompress(char *readthis , char*writein){ // текст это файл ЗАшифрованный 2 это файл куда писать расшифровку
  FILE *in= fopen(readthis,"r");
  FILE*out  = fopen(writein,"w");
if (in==NULL || out == NULL){
      return false;}
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
                res[i+1] = buf1[i] & ~(mask << 7);
                i++;}
          for(i = 0; i < 8; i++){
                if (!(i == 0 && res[i] == 0)){
                if (fprintf(out,"%c",res[i])<0){
                      return false;} }}
          count = 0;
        }
    }

  if (count  > 0){
    for(int i=0 ; i < count; i++){
      if (fprintf(out, "%c",buf1[i]) < 0){
            return false;}
}}
  fclose(in);
  fclose(out);
return true;}







int main()
{

  char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/first.txt");
  char ptr2[1000] = ("/Users/fliruden/vuz/lab_with_file/build/unknown-Debug/second.txt");
  if(Compress(ptr,ptr2)){
    printf("Correct Compress");
}
  else{printf("Wrong Compress");
      return 0;}
  printf("\n");



  if (DeCompress(ptr2,ptr)){
    printf("Correct DeCompress");
}
  else{printf("Wrong DeCompress");
      return 0;}

  return 0;}

