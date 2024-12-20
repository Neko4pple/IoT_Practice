var remoteCon = 'remote_con.php';

$(document).ready(function(){ //$(document) is form of jquery, function() is jquery's ready event handler
  $.ajax({                    //if document is fully loaded, anonymous function() will be called & executed.
    type: "GET",              //and fucntion() has ajax calling method. 
    timeout: 100000           // sets timeout to 100 seconds
  });
  
  /*-----------------------------------------------------------------------------------------------------
  $("#GET_LIGHT").click(function(){ //in jquery, document's "id" field tagged by "#"
    $.get(remoteCon+"?lightLog", function(data, status){
      //alert("Data: " + data + "\nStatus: " + status);
      //$("#LIGHT_val").val(data);
      lightGraph = document.getElementById('lightGraph');
      //console.log(data);
      drawGraph(lightGraph, data);
    });
  });
  ------------------------------------------------------------------------------------------------------*/
  
  $("#GET_TOUCH").click(function(){
    document.TOUCH.src='img/touch_off.png';//in jquery, document's "name" field is tagged as "document.NAME.~~"
    touchAlert();
  });
});

/*--------------------------------------------------------------------------------------------------------
function drawGraph(target, inputData) {
   var xAxis = [1, 2, 3, 4, 5];
   //console.log(inputData);
   var yData = inputData.split(",").map(Number);
   var trace0 = {
     x: xAxis,
     y: yData
   };
   Plotly.plot(target, [trace0]);
}
--------------------------------------------------------------------------------------------------------*/

function touchAlert() {
  $.get(remoteCon+"?touchAlert", function(data, status){//call back function defining.
      console.log(data);                                //setting data viewable.
      document.TOUCH.src='img/touch_on.png';            //change img in _on.
      //$('TOUCH').attr("src", "img/touch_on.png");
      //alert("Touch button has been touched!! \nData: " + data);
  });
}

