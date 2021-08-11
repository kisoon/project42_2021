<H1> LED 제어하기</h1>

1. 42보드의 LED는 WS2812b라는 데이터 통신으로 색상을 변경할 수 있는 LED를 사용합니다.
2. 이 LED를 사용하기위해 Adafruit의 neopixel 라이브러리를 사용합니다.
   네오픽셀 라이브러리 : https://github.com/adafruit/Adafruit_NeoPixel
3. 아두이노IDE로 예제코드를 열어봅시다.
4. 그리고, neopixel 탭을 선택합니다.
 ![image](https://user-images.githubusercontent.com/113105/128957649-d800a060-b313-48c0-8705-f28fd0681bdf.png)
5. 다음 코드를 찾아봅니다.
   <pre><code>
uint32_t ledColor = red;
int brightness = 20;
</code></pre>

6. uint32_t ledColor = red; 
 코드에서 red 대신 red, green, blue, magenta, yellow, white, black중 원하는 색상으로 변경합니다.
7. int brightness = 20; 
 코드는 LED의 밝기를 조절할 수 있습니다. 0~255까지의 숫자를 넣어보세요.
