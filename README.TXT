READ ME

This project uses POSIX threads (pthreads) for multithreading and POSIX semaphores for synchronization. Each phone call is
represented by a separate thread. There are two semaphores: one binary semaphore connected_lock used to protect the critical
section where the connected global variable is updated, and one counting semaphore operators to represent the available operators.

The program accepts a command-line argument representing the total number of phone calls. For each phone call, a new thread is created. 
If the lines are not busy, the thread connects to a line and waits for an operator to become available. After the operator is available,
the appointment is simulated, and then the thread (phone call) finishes.

Some Requirements:

Semaphores: Binary semaphore connected_lock is used to protect the connected global variable. Counting semaphore operators 
represents the available operators. Both semaphores are initialized in the main() function and destroyed at the end of the main() function.

Threads: A separate thread is created for each phone call. The threads are created in the main() function, and the main thread 
waits for all phone call threads to finish before it completes.

Synchronization: The connected_lock binary semaphore is used to protect the connected global variable. If the lines are busy, a 
thread prints a message and tries again. If a line is not busy, the thread connects, waits for an operator, simulates the appointment, and finishes.

Testing: The program has been tested with 1, 10, 20, 50, and 100 phone calls, and runs to completion in all cases.

User Input: The program accepts a command-line argument representing the total number of phone calls. It handles irregular user 
input and no input by defaulting to a predefined number of phone calls.

Error Handling: Error handling is implemented for pthread and semaphore functions. The program does not cause a segmentation fault in any case.

Makefile: The makefile was used to compile the file, and was based on and adjusted from the sample makefile given in instructions.