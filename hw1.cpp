/*
CSIE2 403410010 Chuang Tsung-Ying 2016/3/17
header file introduction:
iostream for console input output
cstdio for testing data freopen
ctime for the time parameter NULL
algorithm for sort ,srand and rand
*/
//build by clang3.4 or g++11 version
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

const int MATRIX_SIZE(10);//the matrix size lock to 10

//generate random element in a matrix,which is call by reference to pass the array to funciton.
void generation(int matrix[][MATRIX_SIZE]);
//print the matrix,which is call by reference to pass the array to  function.
void output(int matrix[][MATRIX_SIZE]);
/*
do the matrix multiply,each matrix are call by reference
*/
void multiplication(int a[][MATRIX_SIZE],int b[][MATRIX_SIZE],int ans[][MATRIX_SIZE]);
//to integrate the median matrix for the complete matrix
void median(int matrix[][MATRIX_SIZE],int out[][MATRIX_SIZE]);
//to initial each edge and corner,two of array are call by reference
void median_initialize(int origin[][MATRIX_SIZE],int matrix[][MATRIX_SIZE]);
//to find the corner's median number,each argument is call by value
int median_corner(int a,int b,int c,int d);
//to find the edge's median number,each argument is call by value
int median_line(int a,int b,int c,int d,int e, int f);
int find_median(int matrix[3][3]);//to find the 3*3 matrix number

int main() {
    //freopen("test.txt","w",stdout);
    int matrix_A[MATRIX_SIZE][MATRIX_SIZE],matrix_B[MATRIX_SIZE][MATRIX_SIZE];
    generation(matrix_A);
    generation(matrix_B);
    /*generate two matrix*/
    cout << "A" << endl;
    output(matrix_A);
    cout << "B" << endl;
    output(matrix_B);
    int matrix_multiply[MATRIX_SIZE][MATRIX_SIZE];//matrix for multiply
    multiplication(matrix_A,matrix_B,matrix_multiply);
    int median_matrix[MATRIX_SIZE][MATRIX_SIZE] = {0};/*matrix for median*/
    median(matrix_multiply,median_matrix);
    return 0;
}

void generation(int matrix[][MATRIX_SIZE]) {
    int i,j;
    srand(time(NULL));
    for(i=0; i<MATRIX_SIZE; i++)
        for(j=0; j<MATRIX_SIZE; j++)
            matrix[i][j] = rand()%256;
}
void output(int matrix[][MATRIX_SIZE]) {
    /*
    Use the function carefully to avoid overflow when give array size greater than 10.
    It will print the exact matrix visuallize on the standard output
    */
    int i,j;
    for(i=0; i<MATRIX_SIZE; i++) {
        for(j=0; j<MATRIX_SIZE; j++)
            cout << matrix[i][j] << "\t";
        cout << endl;
    }
}
void multiplication(int matrix_A[][MATRIX_SIZE],int matrix_B[][MATRIX_SIZE],int ans[][MATRIX_SIZE]) {
    /*
    The answer will b store in matrix 'ans' ,to assure that two of input array would not be change.
    */
    int i,j,k;
    for(i=0; i<MATRIX_SIZE; i++)
        for(j=0; j<MATRIX_SIZE; j++) {
            ans[i][j] = 0;
            for(k=0; k<MATRIX_SIZE; k++)
                ans[i][j] += matrix_A[i][k] * matrix_B[k][j];
        }
    cout << "multiply" << endl;
    output(ans);
}
void median(int matrix[MATRIX_SIZE][MATRIX_SIZE],int out[MATRIX_SIZE][MATRIX_SIZE]) {
    /*
    This function will call other functions to integrate the elements in this array which is for output.
    The kernel code of this function is to fin the median of the 8*8 array in the middle.
    The other function is use to calculate each shape of median such as 2*2,and 2*3.
    */
    int i,j,k,l;
    int tmp[3][3] = {0};
    median_initialize(matrix,out);
    for(i = 1; i < MATRIX_SIZE - 1; i++)
        for(j = 1; j < MATRIX_SIZE - 1; j++) {
            for(k = i - 1; k <= i+1; k++)
                for(l = j - 1; l <= j+1; l++)
                    tmp[k-i+1][l-j+1] = matrix[k][l];
            out[i][j] = find_median(tmp);
        }
    cout << "median" << endl;
    output(out);
}
int find_median(int matrix[3][3]) {
    /*
    use sort function in algorithm to sort the array, and just return the median value.
    */
    int *ptr = (int *)matrix;
    sort(ptr,ptr+9);
    return ptr[4];
}
void median_initialize(int origin[MATRIX_SIZE][MATRIX_SIZE],int matrix[MATRIX_SIZE][MATRIX_SIZE]) {

    matrix[0][0] = median_corner(origin[0][0],origin[0][1],origin[1][0],origin[1][1]);
    matrix[0][9] = median_corner(origin[0][9],origin[1][9],origin[0][8],origin[1][8]);
    matrix[9][0] = median_corner(origin[9][0],origin[8][0],origin[9][1],origin[8][1]);
    matrix[9][9] = median_corner(origin[9][9],origin[9][8],origin[8][9],origin[8][8]);
    int i;
    for(i=1; i<9; i++) {
        matrix[0][i] = median_line(origin[0][i-1],origin[0][i],origin[0][i+1],origin[1][i-1],origin[1][i],origin[1][i+1]);
        matrix[i][0] = median_line(origin[i-1][0],origin[i][0],origin[i+1][0],origin[i-1][1],origin[i][1],origin[i+1][1]);
        matrix[9][i] = median_line(origin[9][i-1],origin[9][i],origin[9][i+1],origin[8][i-1],origin[8][i],origin[8][i+1]);
        matrix[i][9] = median_line(origin[i-1][9],origin[i][9],origin[i+1][9],origin[i-1][8],origin[i][8],origin[i+1][8]);
    }
}
int median_corner(int a,int b,int c,int d) {
    /*
    It will return the value of four input's median.
    */
    int arr[4];
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;
    sort(arr,arr+4);
    return ((arr[1]+arr[2])/2);
}
int median_line(int a,int b,int c,int d,int e,int f) {
    /*
    It will return the value of four input's median. 
    */
    int arr[6];
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;
    arr[4] = e;
    arr[5] = f;
    sort(arr,arr+6);
    return ((arr[2]+arr[3])/2);
}
