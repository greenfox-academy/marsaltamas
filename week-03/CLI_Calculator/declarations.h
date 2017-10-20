#ifndef DECLARATIONS_H
#define DECLARATION_H

void open_screen (void);
void help(void);
void clear(void);
void exit_function(void);
void error_message(void);
void read_input(void);
char *operation_prompt(void);
void input_processor(char input[]);
void bye(void);
void addition(char operand1[], char operand2[]);
void substraction(char operand1[], char operand2[]);
void multiplication(char operand1[], char operand2[]);
void division(char operand1[], char operand2[]);
void modulo(char operand1[], char operand2[]);
void squaring(char operand1[], char operand2[]);
void square_root(char operand1[], char operand2[]);
void logarithm(char operand1[], char operand2[]);
void bin_to(char operand1[], char operand2[]);
void hex_to(char operand1[], char operand2[]);
void dec_to(char operand1[], char operand2[]);
int is_input_valid (char operand1[], char operand2[], char opertr[], char operand_trest[]);
int is_float(char to_check[]);
int is_correct_target_base(char to_convert[]);
int is_correct_base(int convert_from, char to_convert[]);
int is_valid_operator(char opertr[]);
void set_cursor_pos(int x, int y);
int get_cursor_x();
int get_cursor_y();
float float_converter(char to_convert[]);
void b_to_b_converter(int convert_from, char to_convert[], int convert_to);

#endif // DECLARATIONS_H