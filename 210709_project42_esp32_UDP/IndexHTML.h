const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>

<head>

  <title>project42</title>

  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.15.3/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">

  <style>

    html {font-family: Arial;display: inline-block;text-align: center;}

    p { font-size: 1.2rem;}

    body {  margin: 0;}

    .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }

    .content {padding: 10px;}

    .card {background-color: white;box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);}

    .cards {max-width: 700px;margin: 0 auto;display: grid;grid-gap: 2rem;grid-template-columns: repeat(auto-fit, minmax(30px, 2fr));}

    .reading { font-size: 1rem; }
    .button {
      padding: 0px 0px;
      font-size: 14px;
      text-align: center;
      outline: none;
      color: #fff;
      background-color: #0f8b8d;
      border: none;
      border-radius: 5px;
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
      -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }

  </style>

</head>

<body>

  <div class="topnav">
    <h1>42Board Sensor Data</h1>
  </div>

  <div class="content">
    <div class="cards">
      <button id="start" onclick="sensorStart(this)">START</button>
    </div>
   </div>

  <div class="content">
  <h3>Movement Sensor 1</h3>
    <div class="cards">
      <div class="card">
        <p> GX</p><p><span class="reading"><span id="GX1">%GX1%</span> rad/s</span></p>
      </div>
      <div class="card">
        <p> GY</p><p><span class="reading"><span id="GY1">%GY1%</span> rad/s</span></p>
      </div>
      <div class="card">
        <p> GZ</p><p><span class="reading"><span id="GZ1">%GZ1%</span> rad/s</span></p>
      </div>
    </div>


  </div>

  <div class="content">
  <h3>Movement Sensor 2</h3>
    <div class="cards">
      <div class="card">
        <p> GX</p><p><span class="reading"><span id="GX2">%GX2%</span> rad/s</span></p>
      </div>
      <div class="card">
        <p> GY</p><p><span class="reading"><span id="GY2">%GY2%</span> rad/s</span></p>
      </div>
      <div class="card">
        <p> GZ</p><p><span class="reading"><span id="GZ2">%GZ2%</span> rad/s</span></p>
      </div>
    </div>


  </div>

  <div class="content">
    <h3>light Sensor</h3>
    <div class="cards">
      <div class="card">
        <p><span class="reading"><span id="light">%LIGHT%</p>
      </div>
    </div>
  </div>

  <div class="content">
    <h3>sound Sensor</h3>
    <div class="cards">
      <div class="card">
        <p><span class="reading"><span id="sound">%SOUND%</p>
      </div>
    </div>  
  </div>

  <div class="content">
    <h3>touch Sensor</h3>
    <div class="cards">
      <div class="button">
        <p><span class="reading"><span id="touch1">%TOUCH1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="touch2">%TOUCH2%</p>
      </div>
    </div>  
  </div>

  <div class="content">
    <h3>LED</h3>
    <div class="cards">
      <div class="button">
        <p><span class="reading"><span id="led0">%LED0%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%LED1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led2">%LED2%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led3">%LED3%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led4">%LED4%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led5">%LED5%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led6">%LED6%</p>
      </div>
    </div>  
  </div>



<script>

if (!!window.EventSource) {

 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);

 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);


 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);

 
//움직임 센서 1
 source.addEventListener('GX1', function(e) {
//  console.log("GX1", e.data);
  document.getElementById("GX1").innerHTML = e.data;
 }, false);

 
 source.addEventListener('GY1', function(e) {
//  console.log("GY1", e.data);
  document.getElementById("GY1").innerHTML = e.data;
 }, false);


 source.addEventListener('GZ1', function(e) {
//  console.log("GZ1", e.data);
  document.getElementById("GZ1").innerHTML = e.data;
 }, false);

// source.addEventListener('AX1', function(e) {
////  console.log("AX1", e.data);
//  document.getElementById("AX1").innerHTML = e.data;
// }, false);
//
// 
// source.addEventListener('AY1', function(e) {
////  console.log("AY1", e.data);
//  document.getElementById("AY1").innerHTML = e.data;
// }, false);
//
//
// source.addEventListener('AZ1', function(e) {
////  console.log("AZ1", e.data);
//  document.getElementById("AZ1").innerHTML = e.data;
// }, false);

//움직임 센서 2
 source.addEventListener('GX2', function(e) {
//  console.log("GX2", e.data);
  document.getElementById("GX2").innerHTML = e.data;
 }, false);

 
 source.addEventListener('GY2', function(e) {
//  console.log("GY2", e.data);
  document.getElementById("GY2").innerHTML = e.data;
 }, false);


 source.addEventListener('GZ2', function(e) {
//  console.log("GZ2", e.data);
  document.getElementById("GZ2").innerHTML = e.data;
 }, false);

// source.addEventListener('AX2', function(e) {
////  console.log("AX2", e.data);
//  document.getElementById("AX2").innerHTML = e.data;
// }, false);
//
// 
// source.addEventListener('AY2', function(e) {
////  console.log("AY2", e.data);
//  document.getElementById("AY2").innerHTML = e.data;
// }, false);
//
//
// source.addEventListener('AZ2', function(e) {
////  console.log("AZ2", e.data);
//  document.getElementById("AZ2").innerHTML = e.data;
// }, false);

 
//mic sensor
 source.addEventListener('sound', function(e) {
//  console.log("sound", e.data);
  document.getElementById("sound").innerHTML = e.data;
 }, false);

//light sensor
  source.addEventListener('light', function(e) {
//  console.log("light", e.data);
  document.getElementById("light").innerHTML = e.data;
 }, false);

 
//touch sensor
  source.addEventListener('touch1', function(e) {
//  console.log("touch1", e.data);
  document.getElementById("touch1").innerHTML = e.data;
 }, false);
  source.addEventListener('touch2', function(e) {
//  console.log("touch2", e.data);
  document.getElementById("touch2").innerHTML = e.data;
 }, false);

}

function sensorStart(element){
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/"+element.id, true);
//  console.log(element.id);
  xhr.send();
}

</script>

</body>

</html>)rawliteral";
