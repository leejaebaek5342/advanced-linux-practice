## 실행 전 설정

환경에 맞게 아래 값을 수정해야 합니다.

### Makefile - 라즈베리파이 접속 정보
빌드한 서버와 라이브러리를 전송할 라즈베리파이 주소와 경로를 본인 환경에 맞게 수정합니다.

    RASPI_HOST = 사용자명@라즈베리파이_IP
    RASPI_DIR  = ~/전송받을_디렉토리

예- `RASPI_HOST = pi@192.168.0.10`

### client.c - 서버 포트 (선택)
기본 포트는 60000으로 설정되어 있으며 필요 시 수정합니다.
서버(server.c)의 SERVER_PORT와 동일하게 맞춰야 합니다.

    #define SERVER_PORT 60000


## 빌드 및 실행
    # 라이브러리 + 서버(라즈베리파이로 자동 전송) / 클라이언트 빌드
    make

    # 라즈베리파이에서 서버 실행
    sudo ./server

    # 우분투에서 클라이언트 실행
    ./client \[라즈베리파이 IP\]

    # 데몬 로그 확인
    sudo tail -f /var/log/syslog | grep device_server