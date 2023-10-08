#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void summate_strings(char* res, char* operand)
{
    int         i = 51;
    short int   digit_sum;

    while(i >= 0)
    {
        digit_sum = (res[i] - 48) + (operand[i] - 48);
        //printf("digit sum is\t%i\n", digit_sum);
        if (digit_sum >= 10)
        {
            res[i] = (digit_sum - 10) + 48;
            res[i - 1] += 1;
        }
        else {res[i] = digit_sum + 48;}
        //printf("\nnext iteration\n");
        //printf("\nintermediary result is:\t%s\n", res);
        i--;
    }
    return;
}

char    *generate_string(int len_str)
{
    char*   output;
    output = (char*)malloc(sizeof(char) * len_str + 1);
    for(int i = 0; i <= len_str; i++){output[i] = '0';}
    output[len_str] = '\0';
    return (output);
}

int main(int argc, char **argv)
{
    int         fd;
    char        *buff;
    char        *result;

    result = generate_string(52);
    buff = generate_string(52);
    fd = open(argv[1], O_RDONLY);

    //printf("init buff\t\t%s\n", buff);
    if (fd == -1) {printf("File not opened, sorry :-(\n"); exit(-1);};

    while(read(fd, buff + 2, 50))
    {
        //printf("start is: \t\t%s\n", result);
        //printf("adding \t\t\t%s\n", buff);
        summate_strings(result, buff);
        lseek(fd, 2, SEEK_CUR);
    }
    printf("\nFinal result is: \t%s\n", result);
    free(result);
    free(buff);
    close(fd);
    return (0);
}

