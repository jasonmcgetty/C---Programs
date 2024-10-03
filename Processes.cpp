#include <iostream>
#include<unistd.h>
#include <sys/wait.h>
using namespace std;


int main()
{
    pid_t pid = fork();
    if (pid<0)
    {
        cerr << "First fork failed" << endl;
    }
    else if (pid == 0)
    {
        cout << "Hello from child process" << endl;
        cout << "Child PID: " << getpid() << endl;
        cout << "Parent PID (from child): " << getppid() << endl;
        pid_t pid1 = fork();
        if (pid1<0)
        {
            cerr << "Second fork failed" << endl;
        }
        else if (pid1 == 0)
        {
            cout << "Hello from child of child process" << endl;
            cout << "Child of child PID: " << getpid() << endl;
            cout << "Parent PID (from child of child): " << getppid() << endl;
        }
        else
        {
            int status;
            pid_t child_pid = waitpid(-1, &status, 0);
            cout << "Hello from parent process (created in child process)" << endl;
            cout << "Child of child PID (from parent): " << pid1 << endl;
            cout << "Parent PID (aka the original child process): " << getpid() << endl;
        }
    }
    else
    {
        int status;
        pid_t child_pid = waitpid(-1, &status, 0);
        cout << "Hello from parent process" << endl;
        cout << "Child PID (from parent): " << pid << endl;
        cout << "Parent PID: " << getpid() << endl;
    }
    return 0;
}