#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <sys/types.h>

#define GUESS_T 5

struct numbers{
    int g1, g2, g3;
}numbers_t;

struct numbers *nums;

int correct = 0, wrong = 0;

void display(){
    printf("\n| %d | %d | %d |\n", nums->g1, nums->g2, nums->g3);
}

void handler(int sig, siginfo_t *info, void *x){
    int gu1 = 0, gu2 = 0, gu3 = 0;
    system("clear");
    printf("| ? | ? | | ? |");
    printf("\nGuess: ");

    scanf("%d %d %d", &gu1, &gu2, &gu3);
    if(gu1 == nums->g1 && gu2 == nums->g2 && gu3 == nums->g3){
        printf("3/3 Sucess\n");
        correct++;
    } else if(gu1 == nums->g1 && gu2 != nums->g2 && gu3 != nums->g3){
        printf("1/3 Failed\n");
        wrong++;
    } else if(gu1 != nums->g1 && gu2 == nums->g2 && gu3 != nums->g3){
        printf("1/3 Failed\n");
        wrong++;
    } else if(gu1 != nums->g1 && gu2 != nums->g2 && gu3 == nums->g3){
        printf("1/3 Failed\n");
        wrong++;
    } else if(gu1 == nums->g1 && gu2 == nums->g2 && gu3 != nums->g3){
        printf("2/3 Failed\n");
        wrong++;
    } else if(gu1 != nums->g1 && gu2 == nums->g2 && gu3 == nums->g3){
        printf("2/3 Failed\n");
        wrong++;
    } else if(gu1 == nums->g1 && gu2 != nums->g2 && gu3 == nums->g3){
        printf("2/3 Failed\n");
        wrong++;
    } else if(gu1 != nums->g1 && gu2 != nums->g2 && gu3 != nums->g3){
        printf("3/3 Failed\n");
        wrong++;
    }
    if(wrong >= 3 || sig == SIGINT){
        printf("\nCorrect: %d\n Wrong: %d\n", correct, wrong);
        exit(EXIT_SUCCESS);
    }
}

int main(){
    int user = 0;
    char *info = "\nGuessing Game.\nRandom sequence of numbers will appear.\nYou have 5 seconds to remember\nIf you guess wrong 3 times you lose.\n";
    nums = (struct numbers *)malloc(sizeof(numbers_t));
    struct sigaction act;
    
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;

    if(sigaction(SIGALRM, &act, NULL) < 0){
        fprintf(stderr, "%s\n", strerror(errno));
    }
    if(sigaction(SIGINT, &act, NULL) < 0){
         fprintf(stderr, "%s\n", strerror(errno));
    }

    puts(info);
    
    printf("\n(1)start\n(2)exit\n? ");
    scanf("%d", &user);
    if(user > 1){
        exit(EXIT_SUCCESS);
    }
    
    srand(time(NULL));

    while(true){
        alarm(GUESS_T);
        fflush(stdout);
        nums->g1 = rand() % 10;
        nums->g2 = rand() % 10;
        nums->g3 = rand() % 10;
        display();
        scanf("%d", &user);
    }
    free(nums);
    return 0;
}