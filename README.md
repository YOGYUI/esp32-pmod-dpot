# esp32-pmod-dpot
ESP32를 이용한 Digilent Pmod DPOT(Digital Potentiometer) 제어 예제 프로젝트

요구사항
---
espressif의 esp-idf가 필요하다. (submodule로 정의되어 있음)<br>
esp-32 관련 모든 기능은 esp-idf를 통해 구현되었다.
```shell
git submodule update --init
source ./sdk/esp-idf/install.sh
```

디지털 가변저항
---
[AD5160 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/AD5160.pdf)
![ad5160_1.png](./resource/ad5160_1.png)
![ad5160_2.png](./resource/ad5160_2.png)

구현내용
---
- HSPI(SPI2) Mater 모드로 AD5160에 저항 설정값을 전달
- Wi-Fi SoftAP 모드 활성화 (SSID: **YOGYUI-ESP32-TEST**)
- HTTP 서버를 통해 저항값 제어 (Port: **80**)
    - 별도로 프론트엔드 프레임워크 사용하지 않고 html 하드코딩
    - SoftAP 접속 후 브라우저에서 **192.168.4.1**로 접속

펌웨어 빌드 및 업로드
---
esp-idf의 idf.py를 이용해 빌드
```shell
source ./sdk/esp-idf/export.sh
idf.py build
```
마찬가지로 idf.py를 이용해 플래시
```shell
idf.py -p /dev/ttyUSB0 flash
```

데모
---

