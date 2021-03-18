objects = head.h shell_cat.o  shell_echo.c shell_ls.o shell_pwd.o shell_rm.o shell.o shell_cd.o shell_help.o shell_mkdir.o shell_redirect.o shell_wc.o MainFramwork.c head.h
main: $(objects)
	gcc -o main $(objects)
%.o:%.c
	gcc -c $<
clean:
	rm *.o
	rm main