#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int Compress(char * readthis , char*writein)
{
  FILE*in = fopen(readthis,"r");
  FILE*out = fopen(writein,"w");
  if (in==NULL || out == NULL){
      return 2;}

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
    for(int i=0 ; i < count; i++){
      flag = false;
      if((fprintf(out, "%c",buf1[i]))<0){
          return 3;}

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
  FILE *in= fopen(readthis,"r");
  FILE*out  = fopen(writein,"w");
if (in==NULL || out == NULL){
      return 2;}
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
                      return 3;} }}
          count = 0;
        }
    }

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

  char ptr[1000]= ("/Users/fliruden/vuz/lab_with_file/bigtext.txt");
  char ptr2[1000] = ("/Users/fliruden/vuz/lab_with_file/second.txt");
  int result = Compress(ptr,ptr2);
  if(result ==1){
    printf("Correct Compress");
}
  else{printf("Error number: %d",result);
      return 0;}
  printf("\n");


  result = Compress(ptr,ptr2);
  if (result == 1){
    printf("Correct DeCompress");
}
  else{printf("Error number: %d",result);
      return 0;}

  return 0;}

