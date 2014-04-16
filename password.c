#include<termios.h>
#include<stdio.h>
#include<stdlib.h>

#define PASSWORD_LEN 8

int main(){
    
    struct termios initialrsettings, newrsettings;
    char password[PASSWORD_LEN+1];
    
    //get the current settig from the standard input and copy them into the termios structure
    tcgetattr(fileno(stdin), &initialrsettings);
    
    //make a copy of original settings to replace them at the end
    newrsettings = initialrsettings;
    
    //turn off the the ECHO flag on the newrsettings
   newrsettings.c_lflag &= ~ECHO;
    
    printf("Enter password: ");
    
    //set the terminal attributes to newrsettings and read in the password
    if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0)
        fprintf(stderr, "Could not set attributes\n");
    else{
        fgets(password, PASSWORD_LEN,stdin);
        tcsetattr(fileno(stdin), TCSANOW, &initialrsettings);
        fprintf(stdout, "\n You entered %s\n", password);
    }
    exit(0);
}