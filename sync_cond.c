//*************************************************************************
//	> File Name: sync.c
//	> Author: lizhiduo 
//	> Mail: lizhiduo@aliyun.com 
//	> Created Time: 2017年09月05日 星期二 21时20分54秒
//************************************************************************

#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int num = 0;

pthread_t pthread[2];

pthread_mutex_t mux_num;

pthread_cond_t cond_ok = PTHREAD_COND_INITIALIZER;/*init cond_ok*/ 

void * taskA(void * arg){
    int i;
    for(i=0; i<5; i++){
        pthread_mutex_lock(&mux_num);
        
        num++;
        
        printf("taskA : num :%d\n", num);
        if(num==5){
            //
            pthread_cond_signal(&cond_ok);
        }
        pthread_mutex_unlock(&mux_num);
        
        sleep(1);
    }

    //EXIT 
    pthread_exit(NULL);

}

void * taskB(void *arg){

        pthread_mutex_lock(&mux_num);
        
        if(num < 5)
            //
            pthread_cond_wait(&cond_ok, &mux_num);
        
        num = 0;
        
        pthread_mutex_unlock(&mux_num);     
        
        printf("taskB : finish ...\n");

    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    
    //init nutex
    pthread_mutex_init(&mux_num, NULL);

    //new thread in the calling process
    pthread_create(&pthread[0], NULL, taskA, NULL);
    
    pthread_create(&pthread[1], NULL, taskB, NULL);


    // waits for the thread specified by thread to terminate
    pthread_join(pthread[0], NULL);
    pthread_join(pthread[1], NULL);

    return 0;
}
