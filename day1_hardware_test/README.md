# Day 1 - 하드웨어 단독 테스트

## 개요
각 장치를 독립적으로 테스트하는 단계입니다.
모든 장치 제어 함수는 이후 공유 라이브러리로 통합할 것을 고려하여 함수 형태로 작성했습니다.

## 환경
- 서버: Raspberry Pi 4
- 개발: UTM Ubuntu (macOS)

## 파일 구성
| 파일 | 설명 |
|------|------|
| led.c | LED on/off 및 밝기(HIGH/MID/LOW) 제어 테스트 |
| buzzer.c | 부저 on/off 및 음악 재생 테스트 |
| cds.c | PCF8591 I2C 조도센서 값 읽기 테스트 |
| segment.c | SN74LS47N BCD 제어, 0~9 숫자 출력 테스트 |
| temperature.c | PCF8591 I2C 온도센서 값 읽기 테스트 (추가기능) |

## 핀 연결
| 장치 | BCM | wiringPi |
|------|-----|----------|
| LED | - | 1 |
| BUZZER | BCM 22 | 3 |
| SEG_A | BCM 23 | 4 |
| SEG_B | BCM 24 | 5 |
| SEG_C | BCM 25 | 6 |
| SEG_D | BCM 12 | 26 |
| PCF8591 (CDS/TEMP) | I2C 0x48 | - |

## 빌드 및 실행
```bash
make
sudo ./led ON
sudo ./buzzer ON
sudo ./cds
sudo ./segment 5
sudo ./temperature
```

## 체크포인트
- [x] LED on/off/밝기 함수 동작 확인
- [x] 부저 on/off 및 음악 재생 확인
- [x] 조도센서 값 읽기 및 변화 확인
- [x] 7세그먼트 0~9 출력 확인
- [x] 온도센서 값 읽기 확인
