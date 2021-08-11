# project42_2021
42보드 지원 문서에 오신 것을 환영합니다! 여기에서 사용 방법에 대한 정보를 찾을 수 있습니다.

설치 방법
1. 아두이노 프로그램을 설치해주세요. https://www.arduino.cc/en/software 다음 링크에서 자신의 컴퓨터OS환경에 맞는 버전을 다운로드 받으면 됩니다.
2. 아두이노 프로그램을 실행시키고 환경설정 윈도우를 열어주세요.
   win:파일->환경설정(Ctrl+,) / mac:arduino->preference(Command+,)
4. <img src="https://user-images.githubusercontent.com/113105/127854647-e6a15c33-2e30-4120-828a-48a921f55858.png" width="70%" height="70%"/>
5. 그리고 사진의 주황색 칸에 다음 링크를 복사하여 붙여넣고 확인버튼(OK)을 눌러주세요
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
5. 아두이노에서 보드 매니저를 실행하세요. 도구(Tools) 메뉴 -> Board -> 보드 매니저(Board Manager)
<img src="https://user-images.githubusercontent.com/113105/127855026-4d74ebb8-c8ff-45d0-80fd-c78cd27e8f70.png" width="70%" height="70%"/>
6. 보드 매니저를 실행 후 esp32 라고 검색을 해주세요. 설치(instll)버튼을 클릭하여 esp32 보드를 아두이노에 설치합니다.
<img src="https://user-images.githubusercontent.com/113105/127855118-6b8e8cc2-e387-4179-bc3e-1d63285f7680.png" width="70%" height="70%"/>


7. 그리고 아두이노 IDE를 다시 실행시키세요.

8. 다시! 도구(Tools) 메뉴 -> Board에서 ESP32 Arduino -> ESP32 Dev Module을 선택합니다.
  <img src="https://user-images.githubusercontent.com/113105/127861314-c187119f-534d-4fc2-ac5b-ea1e0e0b61ad.png" width="70%" height="70%"/>
9. 마지막으로 자신의 컴퓨터의 설치된 42보드 포트를 선택해야합니다. 포트를 선택하기전 컴퓨터에 드라이버 소프트웨어를 설치합니다.
   42보드에는 cp2104라는 USB포트 인식 칩이 내장되어 있습니다.
   다음 링크에서 자신의 컴퓨터 환경에 맞는 드라이버를 다운받아 설치합니다.
   https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   <img src="https://user-images.githubusercontent.com/113105/127861858-926ac5ec-065e-4b47-a7ee-fd49363417b9.png" width="70%" height="70%"/>
   
10. 드라이버의 설치를 완료한 뒤 다시 아두이노 IDE로 돌아와 도구(Tools) 메뉴에서 port를 확인합니다. 자신의 컴퓨터에 설치된 42보드 포트를 확인할 수 있습니다.
    windows는 COM[숫자]의 형태로 되어있습니다.
   <img src="https://user-images.githubusercontent.com/113105/127997827-501c237e-1fb8-4bcc-82c4-a1d97c048bbb.png" width="70%" height="70%"/>
   
11. 42보드를 사용할 때는 항상 보드이름과 포트를 확인 후 사용합니다.


   

