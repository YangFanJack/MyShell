  #include <stdio.h>
  #include <stdlib.h>
  
  int main(int argc, char *argv[])
  {
      if(argc == 3)//将文件中的打印到标准输出
      {
         FILE *src ;
         FILE *dest;
         if( !( src = fopen( argv[0], "r" ) ) )
         {
             fprintf(stderr, "%s: cannot open file %s\n", argv[0],argv[1]);
             exit(-1);
         }
         if( !( dest = fopen( argv[2], "w+" ) ) )
         {
             fprintf(stderr, "%s: cannot open file %s\n", argv[0],argv[1]);
             exit(-1);
         }
         int c;
         while( (c = fgetc(src))!=EOF)
         {
             fputc(c,dest);
         }
         fclose(src);
         fclose(dest);
     }
     
   return 0;
}
