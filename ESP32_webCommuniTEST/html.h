const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>

<head>

  <title>ESP Web Server</title>

  <meta name="viewport" content="width=device-width, initial-scale=1">

  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">

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

    <h1>MPU6050 WEB SERVER (SSE)</h1>

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

    <div class="cards">
      <div class="card">
        <p> AX</p><p><span class="reading"><span id="AX1">%AX1%</span> g</span></p>
      </div>
      <div class="card">
        <p> AY</p><p><span class="reading"><span id="AY1">%AY1%</span> g</span></p>
      </div>
      <div class="card">
        <p> AZ</p><p><span class="reading"><span id="AZ1">%AZ1%</span> g</span></p>
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

    <div class="cards">
      <div class="card">
        <p> AX</p><p><span class="reading"><span id="AX2">%AX2%</span> g</span></p>
      </div>
      <div class="card">
        <p> AY</p><p><span class="reading"><span id="AY2">%AY2%</span> g</span></p>
      </div>
      <div class="card">
        <p> AZ</p><p><span class="reading"><span id="AZ2">%AZ2%</span> g</span></p>
      </div>
    </div>
  </div>

  <div class="content">
    <h3>빛 센서</h3>
    <div class="cards">
      <div class="card">
        <p><span class="reading"><span id="light">%light%</p>
      </div>
    </div>
  </div>

  <div class="content">
    <h3>소리 센서</h3>
    <div class="cards">
      <div class="card">
        <p><span class="reading"><span id="sound">%sound%</p>
      </div>
    </div>  
  </div>

  <div class="content">
    <h3>터치 센서</h3>
    <div class="cards">
      <div class="button">
        <p><span class="reading"><span id="touch1">%touch1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="touch2">%touch2%</p>
      </div>
    </div>  
  </div>

  <div class="content">
    <h3>LED</h3>
    <div class="cards">
      <div class="button">
        <p><span class="reading"><span id="touch1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
      </div>
      <div class="button">
        <p><span class="reading"><span id="led1">%led1%</p>
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
  console.log("GX1", e.data);
  document.getElementById("GX1").innerHTML = e.data;
 }, false);

 
 source.addEventListener('GY1', function(e) {
  console.log("GY1", e.data);
  document.getElementById("GY1").innerHTML = e.data;
 }, false);


 source.addEventListener('GZ1', function(e) {
  console.log("GZ1", e.data);
  document.getElementById("GZ1").innerHTML = e.data;
 }, false);

 source.addEventListener('AX1', function(e) {
  console.log("AX1", e.data);
  document.getElementById("AX1").innerHTML = e.data;
 }, false);

 
 source.addEventListener('AY1', function(e) {
  console.log("AY1", e.data);
  document.getElementById("AY1").innerHTML = e.data;
 }, false);


 source.addEventListener('AZ1', function(e) {
  console.log("AZ1", e.data);
  document.getElementById("AZ1").innerHTML = e.data;
 }, false);

//움직임 센서 2
 source.addEventListener('GX2', function(e) {
  console.log("GX2", e.data);
  document.getElementById("GX2").innerHTML = e.data;
 }, false);

 
 source.addEventListener('GY2', function(e) {
  console.log("GY2", e.data);
  document.getElementById("GY2").innerHTML = e.data;
 }, false);


 source.addEventListener('GZ2', function(e) {
  console.log("GZ2", e.data);
  document.getElementById("GZ2").innerHTML = e.data;
 }, false);

 source.addEventListener('AX2', function(e) {
  console.log("AX2", e.data);
  document.getElementById("AX2").innerHTML = e.data;
 }, false);

 
 source.addEventListener('AY2', function(e) {
  console.log("AY2", e.data);
  document.getElementById("AY2").innerHTML = e.data;
 }, false);


 source.addEventListener('AZ2', function(e) {
  console.log("AZ2", e.data);
  document.getElementById("AZ2").innerHTML = e.data;
 }, false);



}

</script>

</body>

</html>)rawliteral";
