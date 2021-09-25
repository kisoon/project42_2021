# project42_2021
42보드 지원 문서에 오신 것을 환영합니다! 여기에서 사용 방법에 대한 정보를 찾을 수 있습니다.

-- <a href = https://github.com/kisoon/project42_2021#-%EC%84%A4%EC%B9%98-%EB%B0%A9%EB%B2%95-> 보드 설치방법 </a><br>
-- <a href = https://github.com/kisoon/project42_2021/blob/main/README.md#-%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC-%EC%84%A4%EC%B9%98-%EB%B0%A9%EB%B2%95->라이브러리 설치 방법 </a> <br>
-- <a href = https://github.com/kisoon/project42_2021/blob/main/5-2.%20%ED%95%A8%EA%BB%98%20%EC%82%AC%EC%9A%A9%ED%95%98%EA%B8%B0.md> 함께사용하기 </a>

<H3> 보드 설치 방법 </h3>
1. 아두이노 프로그램을 설치해주세요. https://www.arduino.cc/en/software 다음 링크에서 자신의 컴퓨터OS환경에 맞는 버전을 다운로드 받으면 됩니다.<br>
2. 아두이노 프로그램을 실행시키고 환경설정 윈도우를 열어주세요.<br>
   win:파일->환경설정(Ctrl+,) / mac:arduino->preference(Command+,)<br>
   <img src="https://user-images.githubusercontent.com/113105/127854647-e6a15c33-2e30-4120-828a-48a921f55858.png" width="70%" height="70%"/>
3. 그리고 사진의 주황색 칸에 다음 링크를 복사하여 붙여넣고 확인버튼(OK)을 눌러주세요
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json<br>
4. 아두이노에서 보드 매니저를 실행하세요. 도구(Tools) 메뉴 -> Board -> 보드 매니저(Board Manager)
<img src="https://user-images.githubusercontent.com/113105/127855026-4d74ebb8-c8ff-45d0-80fd-c78cd27e8f70.png" width="70%" height="70%"/><br>
5. 보드 매니저를 실행 후 esp32 라고 검색을 해주세요. 그리고, <b>1.0.6버전</b>을 선택하고, 설치(instll)버튼을 클릭하여 esp32 보드를 아두이노에 설치합니다.
<img src="https://user-images.githubusercontent.com/113105/127855118-6b8e8cc2-e387-4179-bc3e-1d63285f7680.png" width="70%" height="70%"/>


6. 그리고 아두이노 IDE를 다시 실행시키세요.

7. 다시! 도구(Tools) 메뉴 -> Board에서 ESP32 Arduino -> ESP32 Dev Module을 선택합니다.
  <img src="https://user-images.githubusercontent.com/113105/127861314-c187119f-534d-4fc2-ac5b-ea1e0e0b61ad.png" width="70%" height="70%"/>
8. 마지막으로 자신의 컴퓨터의 설치된 42보드 포트를 선택해야합니다. 포트를 선택하기전 컴퓨터에 드라이버 소프트웨어를 설치합니다.
   42보드에는 cp2104라는 USB포트 인식 칩이 내장되어 있습니다.
   다음 링크에서 자신의 컴퓨터 환경에 맞는 드라이버를 다운받아 설치합니다.
   https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   <img src="https://user-images.githubusercontent.com/113105/127861858-926ac5ec-065e-4b47-a7ee-fd49363417b9.png" width="70%" height="70%"/>
   
9. 드라이버의 설치를 완료한 뒤 다시 아두이노 IDE로 돌아와 도구(Tools) 메뉴에서 port를 확인합니다. 자신의 컴퓨터에 설치된 42보드 포트를 확인할 수 있습니다.
    windows는 COM[숫자]의 형태로 되어있습니다.
   <img src="https://user-images.githubusercontent.com/113105/127997827-501c237e-1fb8-4bcc-82c4-a1d97c048bbb.png" width="70%" height="70%"/>
   
10. 42보드를 사용할 때는 항상 보드이름과 포트를 확인 후 사용합니다.

<H3> 라이브러리 설치 방법 </h3>
아두이노 라이브러리 설치 가이드 -> https://www.arduino.cc/en/Guide/Libraries

1. 라이브러리는 아두이노 IDE를 실행하여 설치할 수 있다.<br>
2. 스케치 메뉴 -> 라이브러리 포함하기(include library) -> Manage libraries를 선택한다.<br>
<img src="https://user-images.githubusercontent.com/113105/128958299-70d4bed9-c8ab-4560-a0aa-132b5c980eb3.png" width="70%" height="70%"/>
<img src="https://user-images.githubusercontent.com/113105/128958462-d859e7a3-5550-4666-8845-fbe24e97e6e1.png" width="70%" height="70%"/>

3. 검색창에 다음 라이브러리를 검색한 후 모두 설치를 한다.
   1) Adafruit_MPR121
   2) MPU6050 by electronic cats https://github.com/electroniccats/mpu6050
   3) Adafruit neopixel https://github.com/adafruit/Adafruit_NeoPixel
4. 다운받은 폴더의 libraries안의 AsyncTCP 폴더와 ESPAsyncWebServer 폴더를 문서 -> arduino -> libraries 폴더안에 붙여넣기 합니다.
<img src="https://user-images.githubusercontent.com/113105/129850013-4061971a-e445-43a4-b35a-0c03fd5c2f99.png" width="70%" height="70%"/>




