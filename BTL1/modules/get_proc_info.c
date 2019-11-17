#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

#define STUDENT_ID 1713484

static int pid __initdata = -1;
module_param(pid, int, 0);

struct task_struct *proc;
struct task_struct *parent_proc;
struct task_struct *oldest_child_proc;

struct task_struct *task; //to test
struct list_head *list;   //to test

static int __init get_proc_info_init(void)
{
    printk("Load module success!");
    printk("My student ID: %ld\n", (long)STUDENT_ID);
    printk("pid to find = %d\n", pid);
    if (pid == -1)
    {
        proc = get_current();
    }
    else
    {
        proc = pid_task(find_get_pid(pid), PIDTYPE_PID);
        if (proc == NULL)
        {
            printk("Not found proc with pid = %d!\n", pid);
            return EINVAL;
        }
    }
    printk("Proc ID: %d\n", proc->pid);
    printk("Proc name: %s\n", proc->comm);
    parent_proc = proc->parent;
    if (parent_proc != NULL)
    {
        printk("Parent ID: %d\n", parent_proc->pid);
        printk("Parent name: %s\n", parent_proc->comm);
    }
    else
    { //Co the khong can thiet vi proc nao cung co parent
        printk("This proc does not have parent!\n");
    }
    oldest_child_proc = list_first_entry_or_null(&proc->children, struct task_struct, sibling);
    if (oldest_child_proc != NULL)
    {
        printk("Child ID: %d\n", oldest_child_proc->pid);
        printk("Child name: %s\n", oldest_child_proc->comm);
    }
    else
    {
        printk("This proc does not have any child!\n");
    }
    printk("-------TEST-------\n");
    oldest_child_proc = list_first_entry_or_null(&proc->ptraced, struct task_struct, sibling);
    if (oldest_child_proc != NULL)
    {
        printk("Child ID: %d\n", oldest_child_proc->pid);
        printk("Child name: %s\n", oldest_child_proc->comm);
    }
    else
    {
        printk("This proc does not have any child!\n");
    }
    list_for_each(list, &current->ptraced)
    {
        task = list_entry(list, struct task_struct, sibling);
        printk("%s[%d]\n", task->comm, task->pid);
    }
    return 0;
}

static void __exit get_proc_info_exit(void)
{
    printk("Unload module success!");
}

module_init(get_proc_info_init);
module_exit(get_proc_info_exit);
MODULE_LICENSE("GPL");