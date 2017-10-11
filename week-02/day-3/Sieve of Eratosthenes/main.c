#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int give_me_limit(void);
void array_printer(int arr[][2], int size, int step);

int main()
{
    // setting up limit
    int size = give_me_limit();
    // array hold values up to given limit, at first pos it holds flag, at second it holds value
    /*static*/ int array[1000][2];

    // loding array up to given limit with values and flags - flag 0 = not prime, flag 1 = prime/not checked
    for (int i = 0; i < size; i++) {
        array[i][1] = 1;
        array[i][2] = i;
    }

    array_printer(array, size, 1);

    // changes flag value agains test case
    for (int divider = 2; divider < size; divider++) {
        for (int i = 0; i < size; i++) {
            if (array[i][2] % (divider) == 0)
                array[i][1] = 0;
        }
        // removes flagged items
            for (int k = 0; k < size; k++){
            if (array[k][1] == 0){
                for (int i = k; i < size; i++) {
                    array[i][1] = array[i+1][1];
                    array[i][2] = array[i+1][2];
                }
                k--;
                size--;
             }
        }
    }

     array_printer(array, size, 1);


}

// requests the user to input the upper limit up to which he wants to find primes
int give_me_limit (void)
{
    int size = 0;

    do {
        printf("Please enter a limit up to which you want to list prime numbers (between 1 and 10 000 000): ");
        scanf("%d", &size);
        printf("You entered %d.\n", size);
    } while (size < 1 || size > 1000);

    return size;
}
// prints array up to given size at the rate of give steps
void array_printer (int arr[][2], int size, int step)
{

    for (int i = 0; i < size; i = i + step) {
            printf("Array element flag at pos #%d is %d.\n", i, arr[i][1]);
            printf("Array element value at pos #%d is %d.\n", i, arr[i][2]);

    }

    printf("\n");

}
