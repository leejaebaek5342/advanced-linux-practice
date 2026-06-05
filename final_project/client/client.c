#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define SERVER_PORT 60000
#define MAX_SIZES   256

int sockfd = -1;

void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void signal_setup()
{
    sigset_t set;

    sigfillset(&set);
    sigdelset(&set,SIGINT);
    sigprocmask(SIG_SETMASK,&set,NULL);
}


void handle_led_brightness()
{
    char cmd[MAX_SIZES];
    int menu;

    printf("\n[LED 밝기 조절]\n");
    printf("1. HIGH\n");
    printf("2. MID\n");
    printf("3. LOW\n");
    printf("0. 취소\n");
    printf("선택> ");

    if(scanf("%d",&menu) != 1)
    {
        printf("숫자를 입력하세요.\n");
        clear_input();
        return;
    }

    switch(menu)
    {
        case 1:
            snprintf(cmd,sizeof(cmd),"LED HIGH");
            send(sockfd,cmd,strlen(cmd),0);
            break;

        case 2:
            snprintf(cmd,sizeof(cmd),"LED MID");
            send(sockfd,cmd,strlen(cmd),0);
            break;
        
        case 3:
            snprintf(cmd,sizeof(cmd),"LED LOW");
            send(sockfd,cmd,strlen(cmd),0);
            break;
        
        case 0:
            return;
            break;

        default:
            printf("잘못된 입력 입니다.\n");
            return;
            break;
    }

}

void handle_seg()
{
    int num;
    char cmd[MAX_SIZES];

    printf("7SEG 시작 숫자 입력(0~9): ");

    if(scanf("%d", &num) != 1)
    {
        printf("숫자를 입력하세요.\n");
        clear_input();
        return;
    }

    if(num < 0 || num > 9)
    {
        printf("0~9 사이 숫자만 입력하세요.\n");
        return;
    }

    snprintf(cmd, sizeof(cmd), "SEG %d", num);
    send(sockfd,cmd,strlen(cmd),0);
}

void print_menu()
{
    printf("\n========== 장치 제어 메뉴 ==========\n");
    printf("1. LED ON\n");
    printf("2. LED OFF\n");
    printf("3. LED 밝기 조절\n");
    printf("4. BUZZER ON\n");
    printf("5. BUZZER OFF\n");
    printf("6. 7SEG 카운트다운\n");
    printf("7. CDS 조도센서 값 확인\n");
    printf("8. TEMP 온도 값 확인\n");
    printf("0. 종료\n");
    printf("====================================\n");
    printf("선택> ");
}

void client_init(char* server_ip)
{
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(sockfd);
        exit(1);
    }

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    printf("서버 연결됨: %s:%d\n", server_ip, SERVER_PORT);
    return;
}

void run_menu()
{
    while(1)
    {
        int menu,numbytes;
        char cmd[MAX_SIZES];

        print_menu();

        if(scanf("%d", &menu) != 1)
        {
            printf("숫자를 입력하세요.\n");
            clear_input();
            continue;
        }

        switch(menu)
        {
            case 1: 
                snprintf(cmd,sizeof(cmd),"LED ON");
                send(sockfd,cmd,strlen(cmd),0);
                break;
            
            case 2:
                snprintf(cmd,sizeof(cmd),"LED OFF");
                send(sockfd,cmd,strlen(cmd),0);
                break;

            case 3:
                handle_led_brightness();
                break;
            
            case 4:
                snprintf(cmd,sizeof(cmd),"BUZZER ON");
                send(sockfd,cmd,strlen(cmd),0);
                break;

            case 5:
                snprintf(cmd,sizeof(cmd),"BUZZER OFF");
                send(sockfd,cmd,strlen(cmd),0);
                break;

            case 6:
                handle_seg();
                break;
            case 7:
                snprintf(cmd,sizeof(cmd),"CDS");
                send(sockfd,cmd,strlen(cmd),0);
                numbytes = read(sockfd,cmd,MAX_SIZES - 1);
                if(numbytes <= 0)
                {
                    printf("서버 연결 종료\n");
                    close(sockfd);
                    exit(1);
                }
                cmd[numbytes] = '\0';
                printf("%s\n",cmd);
                break;
            
            case 8:
                snprintf(cmd,sizeof(cmd),"TEMP");
                send(sockfd,cmd,strlen(cmd),0);
                numbytes = read(sockfd,cmd,MAX_SIZES - 1);
                if(numbytes <= 0)
                {
                    printf("서버 연결 종료\n");
                    close(sockfd);
                    exit(1);
                }
                cmd[numbytes] = '\0';
                printf("%s\n",cmd);
                break;
            
            case 0:
                printf("클라이언트 종료\n");
                close(sockfd);
                exit(0);
                break;
            
            default:
                printf("잘못된 메뉴입니다.\n");
                break;
        }
    }
}

int main(int argc,char** argv)
{    
    signal_setup();

    if(argc != 2)
    {
        printf("사용법: %s <서버 IP>\n", argv[0]);
        exit(1);
    }

    client_init(argv[1]);

    run_menu();

    return 0;
}
