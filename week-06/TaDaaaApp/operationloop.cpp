#include "operationloop.h"
#include "screentemplate.h"
#include "inputprocessor.h"


void OperationLoop::operationPrompt()
{
    //system("cls");
    ScreenTemplate st;
    st.print_header();
    Tasks t;
    t.print_tasks();
    st.print_foot();
    InputProcessor ip;
    ip.command_selector(ip.get_input()); //getting input as string and passing it to tokenizer
}
