#include <iostream>
#include <cmath>

using namespace std;

double** create_first_row_minor(double **mtr, int size, int col) //create n minors by deleting the 1st row and ith column
{
    double **minor = new double*[size - 1];
    for(int i = 0; i < size - 1; i++)
    {
        minor[i] = new double[size - 1];
    }
    
    
    
    for(int i = 0; i < col; i++)
    {
        for(int j = 0; j < size - 1; j++)
        {
            minor[j][i] = mtr[j+1][i];
        } 
    }    
    
    for(int i = col; i < size - 1; i++)
    {
        for(int j = 0; j < size - 1; j++)
        {
            minor[j][i] = mtr[j+1][i+1];
        } 
    }
    return minor;
}


double get_determinant( double **mtr, int size) // using cofactor expansion
{
    double determinant = 0.00;
    //1st base case: 1x1
    if(size == 1)
    {
        determinant = mtr[0][0];
    }
    
    //2nd base case: 2x2
    else if(size == 2)
    {
        determinant = (mtr[0][0]*mtr[1][1]) - (mtr[0][1]*mtr[1][0]);
    }
    
    else
    {
        for(int i = 0; i< size; i++)
        {
            determinant += mtr[0][i]*pow(-1,i+2)*get_determinant(create_first_row_minor(mtr, size, i), size - 1);
        }
    }
    return determinant;
}

void mtrdisplay(double** mtr, int size) //displays an nxn matint
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << mtr[i][j] << "    ";
        }
        cout << endl;
    }
}

double** replace_column(double **A, double *B, int size, int col) 
{
    /*function that swaps the coefficients of the ith variable switch
    the column of constants*/
    double **mtr = new double*[size];
    for(int i = 0; i < size; i++)
    {
        mtr[i] = new double[size];
    }
    
    for (int i = 0; i < size; i++)
    {
        if(i == col)
        {
            for (int j = 0; j < size; j++)
            {
                mtr[j][i] = B[j];
            }
        }
        
        else
        {
            for (int j = 0; j < size; j++)
            {
                mtr[j][i] = A[j][i];
            }
        }
    }
    return mtr;
}

double* cramer(double **A, double *B, int size)
{
    double* x_values = new double[size];
    double det_A = get_determinant(A, size);
    if(det_A == 0)
    {
        cout<<"matrix is singular\nCramer's rule not applicable\n";
        exit(-1);
    }
    for (int i = 0; i < size; i++)
    {
        x_values[i] = (get_determinant(replace_column(A,B,size,i),size)/det_A);
    }
    return x_values;
}

int main()
{
    cout<<"Square matrix solver\nCramer's Rule\n\nEnter the size of your square matrix:\n";
    int n;
    cin>>n;
    
    
    double **matrix = new double*[n];
    for(int i = 0; i < n; i++)
    {
        matrix[i] = new double[n];
    }
    
    for (int i = 0; i < n; i++)
    {
        cout<<"\nenter the coefficients of equation number "<<i+1<<endl;
        for (int j = 0; j < n; j++)
        {
            cin>>matrix[i][j];
            
        }
    }
    
    double* s = new double[4];
    
    cout<<"\nenter the column of constants"<<endl;
    for (int i = 0; i < n; i++)
    {
        cin>>s[i];
        cout<<endl;
    }
    
    
    
    
    
    double* x = new double[n];
    
    x = cramer(matrix, s, n);
    
    
    for(int i = 0; i < n; i++)
    {
        cout<<"X"<<i+1<<" = "<<x[i]<<"\n";
    }
  
    return 0;
}


