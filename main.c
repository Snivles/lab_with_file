#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


bool Compress(char * readthis , char*writein)
{
  FILE*in = fopen(readthis,"r");
  FILE*out = fopen(writein,"w");
  if (in==NULL || out == NULL){
      return false;}

  char el;
  unsigned char buf1[8];
  int count = 0;
  bool flag = true;

  unsigned char result;

  while (fscanf(in,"%c",&el)!= -1)
  {
    buf1[count] = el;
    if(buf1[count] > 127 || buf1[count] == 0){
        fclose(in);
        fclose(out);
        if(remove(writein)==0){
        return false;}}

    count++;
    if(count == 8){
      int i = 0;
      while (i < 7){
        result = (buf1[i+1] | ( (buf1[0] >> i)&1 )<<7);
        if(fprintf(out, "%c",result)<0){
            return false;}
        flag = false;
        i++;
        }
      count = 0;
      }
}

  if (count  > 0){
    for(int i=0 ; i < count; i++){
      flag = false;
      if((fprintf(out, "%c",buf1[i]))<0){
          return false;}

  }
}

  if (flag == true){
        fclose(in);
        fclose(out);
        if(remove(writein)==0){
        return false;}}

  fclose(in);
  if(fclose(out) != 0){
    remove(writein);
    return false;}
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
  if(fclose(out) != 0){
    remove(writein);
    return false;}
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

