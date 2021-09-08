<H1> LED 제어하기</h1>

1. 42보드의 LED는 WS2812b라는 데이터 통신으로 색상을 변경할 수 있는 LED를 사용합니다.
2. 이 LED를 사용하기위해 Adafruit의 neopixel 라이브러리를 사용합니다.
   네오픽셀 라이브러리 : https://github.com/adafruit/Adafruit_NeoPixel
3. 아두이노IDE로 예제코드를 열어봅시다.
4. 그리고, neopixel 탭을 선택합니다.
 ![image](https://user-images.githubusercontent.com/113105/128957649-d800a060-b313-48c0-8705-f28fd0681bdf.png)
5. 밝기 변경하는 법.
   5-1. 20번째 줄의 다음 코드를 찾아봅니다.<br>
   <pre>
   <code>
      int brightness = 20;<br>
   </code></pre>

   5-2. int brightness = 20; <br>
        코드는 LED의 밝기를 조절할 수 있습니다. 0~255까지의 숫자를 넣어보세요.<br>
   5-3. 코드를 수정했으면, 다시 보드에 업로드를 합니다.<br>
6. 색상 변경하는 법
   "project42_esp32_UDP" 탭에서 165번째 줄로 이동해봅니다.
    <pre>
   <code>
      #ifdef LED
         ledColor = green; //red, green, blue, magenta, yellow, cyan, white, black
      //  ledShow(ledColor);
      //  ledBlink(ledColor, 500);
      //  ledRainbow(20);
      #endif
   </code></pre>
   6-1. Led 색상 변경하기
   ledColor = green; 다음 코드에서 green 대신 원하는 색상 컬러를 다음에서 골라 입력하세요.
   <red, green, blue, magenta, yellow, cyan, white, black>
   그리고, ledShow(ledColor);를 주석 해제하여 활성화 시킵니다.
   6-2. Led  깜박이기
   ledColor = green; 다음 코드에서 green 대신 원하는 색상 컬러를 다음에서 골라 입력하세요.
   <red, green, blue, magenta, yellow, cyan, white, black>
   그리고, ledBlink(ledColor, 500);를 주석 해제하여 활성화 시킵니다.
   500이라는 숫자대신 다른 숫자를 넣어줍니다. 1000 = 1초, 500 = 0.5초의 시간입니다.
   6-3. Led 무지개
   ledRainbow(20);를 주석 해제하여 활성화 시킵니다.
   20이라는 숫자대신 다른 숫자를 넣어줍니다. 숫자가 작을수록 변화가 빨라집니다.
   
