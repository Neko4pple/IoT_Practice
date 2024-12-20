var remoteCon = 'remote_con_quiz07.php';

$(document).ready(function(){
  $.ajax({
    type: "GET",
    timeout: 100000 // sets timeout to 100 seconds
  });
  $("#GET_LIGHT").click(function(){
    $.get(remoteCon+"?lightLog", function(data, status){
      //alert("Data: " + data + "\nStatus: " + status);
      //$("#LIGHT_val").val(data);
      lightGraph = document.getElementById('lightGraph');
      //console.log(data);
      drawGraph(lightGraph, data);
    });
  });
  
  $("#GET_TOUCH").click(function(){
    document.TOUCH.src='img/touch_off.png';
    touchAlert();
  });
});

function drawGraph(target, inputData) {
   var xAxis = [1, 2, 3, 4, 5];
   //console.log(inputData);
   var yData = inputData.split(",").map(Number); //inputData로 받아오는건 lightLog.txt의 값들. 즉, 쓰여질때마다 갖고온다 > 그 값이 y축값이 된다 > 그래프가 그려진다.
   var trace0 = {
     x: xAxis,
     y: yData
   };
   Plotly.plot(target, [trace0]);
}

function touchAlert() {
  $.get(remoteCon+"?touchAlert", function(data, status){
      console.log(data);
      document.TOUCH.src='img/touch_on.png';
      //$('TOUCH').attr("src", "img/touch_on.png");
      //alert("Touch button has been touched!! \nData: " + data);
  });
}

