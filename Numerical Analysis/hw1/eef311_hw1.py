import numpy as np

path_to_input_file = 'Python\\Numerical Analysis\\hw1\\input2.txt'
path_to_output_file = 'Python\\Numerical Analysis\\hw1\\output.txt'
path_to_output_results_file = 'Python\\Numerical Analysis\\hw1\\output_results2.txt'
iteration_limit = 1000
tolerance =1e-4

# Ax = b equation format is used for variable naming

# reads the txt file and returns the A,b and size 
def read_txt(filepath):
    try:
        with open(filepath, 'r') as file: # opening the file         
            size = file.readline() # reading the first line for getting the size value

            equal_sign_pos =  size.find('=') # finding the '=' mark since the value will come right after that

            if equal_sign_pos != -1: # if '=' is found:
                size = size[equal_sign_pos + 1:] # extracting the size value 
                size = int(size) # taking the size value as an integer
            
            coeff_lines = file.readlines() # reading the matrix lines since the pointer has already passed size line
            coeff_lines = [coeff_line.strip() for coeff_line in coeff_lines] # deleting '\n' values from the coeff_lines array
            coeff_lines = np.array(coeff_lines) # creates a np array filled with the data in coeff_lines

            # split--> rearranges the string "int1 int2" as "['int1', 'int2']"
            # map --> rearranges the list "['int1', 'int2']" as "[int1, int2]"
            # list --> changes the datatype from string to list
            coeff_arr = [list(map(int, coeff.split())) for coeff in coeff_lines] 
            
            A = np.arange(size*size, dtype=float).reshape(size,size) # creating the A matrix with proper dimensions for using inside the function 
            b = np.arange(1*size, dtype=float).reshape(size,1) # creating the b matrix with proper dimensions for using inside the function 
            
            # assigning the proper values to the A and b matrixes
            for row in range(0,size + 1):
                for column in range(0,size):
                    if row == size:
                        b[column] = coeff_arr[row][column]

                    else:
                        A[row][column] = coeff_arr[row][column]

            return A,b,size
            

    except FileNotFoundError: # Exception handling
        print("File not found!")

# gets the size, A and b; makes the necessary adjustments and writes the equation into the file
def write_txt(filepath,size,A,b):

    with open(filepath, "a") as file:
        Ax = "" # will be used for storing the left side of the equation as a string
        result = "" # will be used for storing the right side of the equation as string
        output = "" # will be used for storing the equation as a string
        
        # Assinging the coefficients and number of x's and writing it into the file
        for row in range(0, size):
            for column in range(0, size):
                    
                coef = A[row][column]

                Ax = Ax + f"+{coef}x{column} "


            result = f"= {b[row][0]}" # assigning the b value of the row to a string
            output = Ax + result + "\n" # creating the equation

            # Reseting the strings
            Ax = ""
            result = ""
      
            file.write(output)# Writing to the file

# solves the system by using Gauss Eliminination Method and writes the x variables to the file (Also indicates it if there are infinite solutions)
def gauss_elimination(filepath,size,A,b):
    output = "The solution of the system by Gauss Elimination:\n"

    with open(filepath, "a") as file:
        for i in range(0, size-1): # except the last column
            for j in range (i + 1, size):
                #A[i][i] corresponds to the pivot variable of the columnth row
                factor = A[j][i] / A[i][i] # finding the necessary factor for substracting one row from another

                for column in range(i, size):
                    print(float(factor * A[j,column]))
                    A[j,column] =  A[j,column] - factor * A[i,column] # the substraction in the A matrix for obtaining Row Echalon Form
                
                b[j] = b[j] - factor * b[i] # the substraction in the b column for obtaining final form

        x = np.zeros(size, dtype=float) # creating the x matrix

        if A[size -1][size -1] != 0:
            x[size - 1] = b[size - 1] / A[size - 1][size - 1] # finding the size'th x value
            
            for row in range(size - 2, -1, -1): # starting from the (size - 1)'th x and going to x0
                x_terms = 0 # sum of all x values except i'th one

                for column in range(row + 1, size):
                    x_terms += A[row,column] * x[column] # adding all x values in the system except i'th one

                if A[row][row] != 0:
                    x[row] = (b[row] - x_terms) / A[row, row] # finding the i'th x
                else:
                    file.write("Dependent Matrix! Infinite solutions")
                    file.close()
        
            for x_number in range(size):
                x[x_number] = np.round(x[x_number], 4)
                output = output + f"x{x_number}={x[x_number]}\n"

            file.write(output)
            file.close()
       
        else:
            file.write("Dependent Matrix! Infinite solutions")
            file.close()
# solves the system by using Jacobi Method and writes the x variables to the file (Also indicates it if the iteration limit is reached)
def jacobi_method(filepath,size,A,b):
    x = np.zeros(size, dtype=float)
    x_calc = np.zeros(size,dtype=float)
    output = "The solution of the system by Jacobi Method:\n"
    solution_flag = False
    
    with open(filepath,"a") as file:

        for iteration in range(iteration_limit):
            for row in range(size): # for every row in matrix A
                temp = 0
                for column in range(size): # for every column in matrix A
                    if column != row: # if the x variable is not the one we are looking for
                        temp += A[row][column] * x[column] # multiply the variable with its coefficient and add with previous ones

                x_calc[row] = (b[row] - temp) / A[row][row] # find the variable we are looking for by subtracting temp from the result and dividing by its coefficient
                x_calc[row]= np.round(x_calc[row], 4) # round the fourth digit after the decimal

            if (abs(x_calc - x) < tolerance).all(): # checking if the answers found are close enough to real answers 
                solution_flag = True # states that the answer has been found
                break

            else:           
                if iteration + 1 == iteration_limit: # checkes if the iteration limit is reached or not
                    break     
                x =  np.copy(x_calc) # copying solutions to x for further iterations
            
        # adjusting the output string for writing to file
        if solution_flag: # if the solution has been found
            for x_number in range(size):
                output = output + f"x{x_number}={x[x_number]}\n"
        else:
            # stating that the iteration limit has been reached and writing last found x values to the file
            output = f"Iteration limit reached with {iteration_limit} iterations! Last found x values are:\n"
            for x_number in range(size):
                output = output + f"x{x_number}={x[x_number]}\n"
                              

        file.write(output)
        file.close()

if __name__ == '__main__':
    A,b,size = read_txt(path_to_input_file)

    #write_txt(path_to_output_file,size,A,b)

    #gauss_elimination(path_to_output_results_file,size,A,b)

    #jacobi_method(path_to_output_results_file,size,A,b)
    
