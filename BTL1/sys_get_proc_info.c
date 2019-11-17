#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

#define STUDENT_ID 1713484

struct proc_info
{
	pid_t pid;
	char name[16];
};

struct procinfos
{
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
};

struct task_struct *proc;
struct task_struct *parent_proc;
struct task_struct *oldest_child_proc;

SYSCALL_DEFINE2(get_proc_info, pid_t, pid, struct procinfos *, info)
{
	printk("My student ID: %ld\n", (long)STUDENT_ID);
	printk("pid to find = %d\n", pid);
	if (pid == -1)
	{
		proc = current;
	}
	else if (pid == 0)
	{
		proc = &init_task;
	}
	else
	{
		proc = find_task_by_vpid(pid);
		if (proc == NULL)
		{
			printk("Not found proc with pid = %d!\n", pid);
			return EINVAL;
		}
	}
	info->studentID = STUDENT_ID;
	printk("Proc ID: %d\n", proc->pid);
	printk("Proc name: %s\n", proc->comm);
	info->proc.pid = proc->pid;
	sprintf(info->proc.name, proc->comm);
	parent_proc = proc->parent;
	if (parent_proc != NULL)
	{
		printk("Parent ID: %d\n", parent_proc->pid);
		printk("Parent name: %s\n", parent_proc->comm);
		info->parent_proc.pid = parent_proc->pid;
		sprintf(info->parent_proc.name, parent_proc->comm);
	}
	else //Khong can thiet vi proc nao cung co parent
	{
		printk("This proc does not have parent!\n");
		info->parent_proc.pid = -1;
	}
	if (!list_empty(&proc->children))
	{
		oldest_child_proc = list_first_entry(&proc->children, struct task_struct, sibling);
		printk("Child ID: %d\n", oldest_child_proc->pid);
		printk("Child name: %s\n", oldest_child_proc->comm);
		info->oldest_child_proc.pid = oldest_child_proc->pid;
		sprintf(info->oldest_child_proc.name, oldest_child_proc->comm);
	}
	else
	{
		printk("This proc does not have any child!\n");
		info->oldest_child_proc.pid = -1;
	}
	return 0;
}
