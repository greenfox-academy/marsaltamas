#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define COMMANDS 9

/* OPERATION
 * checking for existing txt file
 * if exists, reading in txt and uploading task_list array
 * printing usage
 * operation_prompt to read input line and forward it to input_processor
 * input_processor processes input until first space, and calls proper command, or sends error message
 * command takes input lie as argument and processes it further, executing command, or sending error message
 * control back to op_prompt
 */

typedef struct Task {
    char description[100];
    int priority;
    struct Checked {
        char checked_display[4];
        int is_checked;
    } checked;
    //struct Task *next;
} Task;

void print_usage(void);
void operation_prompt(void);
void input_processor(char input[]);

char commands[COMMANDS][3] = {"-a", "-wr", "-rd", "-l", "-e", "-rm", "-c", "-p", "-lp"};
Task task_list[10];

void add_task(Task *task_list)
{
    Task new_task;
    gets(new_task.description);
    fflush(stdin);
    scanf("%d", &new_task.priority);
      fflush(stdin);
    gets(new_task.checked.checked_display);
      fflush(stdin);
    scanf("%d", &new_task.checked.is_checked);
      fflush(stdin);

    for (int i = 0; i < 10; i++) {
        if (task_list[i].priority != 1) {
            task_list[i] = new_task;
            break;
        }
    }
}

void task_printer(Task *task_list)
{
    printf("\t\t\t|TASK LIST|\nNum Chk Pri| Task Description\n=======================================================\n");
    for (int i = 0; i < 10; i++) {
            if (task_list[i].priority) {
                printf("%3d ", i +1);
                printf("%s\t", task_list[i].checked.checked_display);
                printf(" %d | ", task_list[i].priority);
                printf("%s\n", task_list[i].description);
                //printf("is_checked: %d\n", task_list[i].checked.is_checked);
                printf("_______________________________________________________\n");
            }
    }
}

int main()
{

    Task test_task = {"task 1", 1, "[x]", 1};
    Task test_task2 = {"task 2", 1, "[x]", 1};
    Task test_task3 = {"task 3", 1, "[x]", 1};
    task_list[0] = test_task;
    task_list[1] = test_task2;
    task_list[2] = test_task3;
    //add_task(task_list);
    //add_task(task_list);

    task_printer(task_list);
    //print_usage();
    return 0;
}

void print_usage(void)
{
    printf( "           Todo application\n"
            "========================================\n"
            "Commands:\n"
            "-a   Adds a new task\n"
            "-wr  Write current todos to file\n"
            "-rd  Read todos from a file\n"
            "-l   Lists all the tasks\n"
            "-e   Empty the list\n"
            "-rm  Removes a task\n"
            "-c   Completes a task\n"
            "-p   Add priority to a task\n"
            "-lp  Lists all the tasks by priority\n");

    operation_prompt();
}

void input_processor(char input[]){

    char command[4];
    char *tokenizer;

    tokenizer = strtok(input, " ");
    strcpy(command, tokenizer);

    printf("%s\n", command);

}

void operation_prompt(void)
{
    char input[100];

    input_processor(gets(input));
}
