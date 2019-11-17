#include <get_proc_info.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static struct procinfos info;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }
    long return_value;
    pid_t pid = (pid_t)atoi(argv[1]);
    return_value = get_proc_info(pid, &info);
    if (return_value != 0)
    {
        fprintf(stderr, "Proccess with pid = %d not found!\n", pid);
        return -1;
    }
    printf("My StudentID = %ld\n", info.studentID);
    printf("Proc ID: %d\n", info.proc.pid);
    printf("Proc name: %s\n", info.proc.name);
    if (info.parent_proc.pid != -1)
    {
        printf("Parent ID: %d\n", info.parent_proc.pid);
        printf("Parent name: %s\n", info.parent_proc.name);
    }
    else
    { //Co the khong can thiet vi proc nao cung co parent
        printf("This proc does not have parent!\n");
    }
    if (info.oldest_child_proc.pid != -1)
    {
        printf("Child ID: %d\n", info.oldest_child_proc.pid);
        printf("Child name: %s\n", info.oldest_child_proc.name);
    }
    else
    {
        printf("This proc does not have any child!\n");
    }
    return 0;
}