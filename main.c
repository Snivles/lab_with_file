#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int Compress(char * readthis , char*writein)
{
 if (readthis == NULL || writein == NULL){return 2;}

FILE*in = fopen(readthis,"r");
if (in == NULL){
      return 2;}

FILE*out = fopen(writein,"w");
  if (out == NULL){
      if(in){
        fclose(in);
        return 2;}}

  fseek(in, 0, SEEK_END);
  long sz = ftell(in);
  fseek(in, 0, SEEK_SET);

  if (sz > 0 && (sz%8)==7){
        fprintf(out,"7\n");
}


  unsigned char el;
  unsigned char buf1[8];
  int count = 0;
  bool flag = true;

  unsigned char result;

  while (fscanf(in,"%c",&el)!= -1)
  {
    buf1[count] = el;
    if(buf1[count] > 127){
        fclose(in);
        if(fclose(out) != 0){
          if(remove(writein)==0){
          return 5;}
          return 6;}
        remove(writein);
        return 4;}

    count++;
    if(count == 8){
      int i = 0;
      while (i < 7){
        result = (buf1[i+1] | ( (buf1[0] >> i)&1 )<<7);
        if(fprintf(out, "%c",result)<0){
            return 3;}
        flag = false;
        i++;
        }
      count = 0;
      }
}

  if (count  > 0){
    flag = false;{
    for(int i=0 ; i < count; i++){
      flag = false;
      if((fprintf(out, "%c",buf1[i]))<0){
          return 3;}}

  }
}

  if (flag == true){
        fclose(in);
        fclose(out);
        remove(writein);
        return 0;}

  fclose(in);
  if(fclose(out) != 0){
    remove(writein);
    return 5;}
return 1;}





int DeCompress(char *readthis , char*writein){
 if (readthis == NULL || writein == NULL){return 2;}

FILE*in = fopen(readthis,"r");
if (in == NULL){
      return 2;}

FILE*out = fopen(writein,"w");
  if (out == NULL){
      if(in){
        fclose(in);
        return 2;}}
  unsigned char f1,f2;
  bool hvost7 = false;
  if (fscanf(in, "%c", &f1) == 1 && fscanf(in, "%c", &f2) == 1){
     if (f1== '7' && f2=='\n'){
          hvost7=true;
} // хвост есть
     else{
        fseek(in,0,SEEK_SET);}} // хвоста нет
  else{
    fseek(in,0,SEEK_SET);}
  fseek(in,0,SEEK_END);
  long razmer;
  long sz = ftell(in);
  if (hvost7){
    razmer = sz-7;
    sz = 2;
    fseek(in,2,SEEK_SET);
}
  else{razmer= (sz/7)*7;
  sz = 0;
  fseek(in, 0, SEEK_SET);}


  unsigned char el;
  unsigned char buf1[7];
  int count = 0;
  unsigned char mask = 1;

  while (sz < razmer && fscanf(in,"%c",&el)!= -1){
      sz++;
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
                if (fprintf(out,"%c",res[i])<0){
                      return 3;} }
          count = 0;
        }}


  if (count  > 0){
    for(int i=0 ; i < count; i++){
      if (fprintf(out, "%c",buf1[i]) < 0){
            return 3;}
}}
  fclose(in);
  if(fclose(out) != 0){
    if(remove(writein)==0){
    return 5;}
  return 6;}
return 1;}







int main()
{
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/bigtext.txt"); // да
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/ascii.txt"); // да
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/file.txt"); // верно, ошибка
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/kirill.txt"); // верно, ошибка
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/pystota.txt"); // пустой файл(без символов) верно
  char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/fifteen.txt");
  //char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/sixteen.txt");
  char ptr2[1000] = ("/Users/fliruden/vuz/lab_with_file/second.txt");
  int result = Compress(ptr,ptr2);
  if(result ==1){
    printf("Correct Compress");
}
  else{printf("Error number: %d",result);
      return 0;}
  printf("\n");


  result = DeCompress(ptr2,ptr);
  if (result == 1){
    printf("Correct DeCompress");
}
  else{printf("Error number: %d",result);
      return 0;}

  return 0;}

