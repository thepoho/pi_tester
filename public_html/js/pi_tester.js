PiTester = {
  websocket: null,
  startup: function(){
    PiTester.websocket = new WebSocket("ws://"+location.host+"/ws");
    PiTester.websocket.onopen = PiTester.socketOnOpen;
    PiTester.websocket.onmessage = PiTester.socketOnMessage;
    PiTester.websocket.onclose = function(ev) {console.log(ev);}

    $("button.shift_out_new_line").click(function(){
      var row = $("tr.shift_out_row.first_row");
      $("table.shift_out").append("<tr class='shift_out_row'>"+row.html()+"</tr>");
      PiTester.shiftOutRowBind();
    });

    PiTester.shiftOutRowBind();

    $("button.shift_out_send").click(function(){
      PiTester.sendShiftOut();
    });

    // $("select.game_state").change(function(){
    //   var data = {
    //     message: "set_game_state", 
    //     value: parseInt($(this).val())
    //   };
    //   PiTester.sendMessage(data);
    // });
  },

  sendShiftOut: function(){
    var send = {message: "shift_out",
      data: [], 
      data_pin: parseInt($("input.shift_out_data").val()),
      clock_pin: parseInt($("input.shift_out_clock").val()),
      latch_pin: parseInt($("input.shift_out_latch").val())
    };
    
    $.each($("tr.shift_out_row td input.shift_row"), function(idx, e){
      e = $(e);
      var tmp = 0;
      if(e.is(':checked')){
        tmp = 1;
      }
      send.data.push(tmp);
    });
    console.log(send);
    PiTester.sendMessage(send);

  },

  shiftOutRowBind: function(){
    $("button.shift_out_delete").unbind();
    $("button.shift_out_delete").click(function(){
      var parent = $(this).parents("tr");
      if(!parent.hasClass("first_row")){
        parent.remove();
      }
    });
    $("tr.shift_out_row td").unbind();
    $("tr.shift_out_row td").click(function(){
      $(this).find("input").click();
      PiTester.sendShiftOut();      
    })

    
    $("input.shift_row").unbind();
    $("input.shift_row").click(function(){
      PiTester.sendShiftOut();      
    })
  },

  socketOnMessage: function(ev){
    console.log("WS response: "+ev.data);

    var data = $.parseJSON(ev.data);
    if(data.name == "get_pins"){
      PiTester.handleGetPinsResponse(data.data);
    }
    
  },

  socketOnOpen: function(ev){
    PiTester.sendMessage({message: "get_pins"});
  },

  sendMessage: function(hash){
    var data = JSON.stringify(hash);
    PiTester.websocket.send(data);
  },

  log: function(str){
    var textarea = $("textarea.log");
    textarea.append(str+"\n");
    textarea[0].scrollTop = textarea[0].scrollHeight;
  },

  handleGetPinsResponse: function(pin_data){
    var direction = "<select class='direction'><option value=''>Not Set</option><option value='out'>Out</option><option value='in'>In</option></select>";
    var state = "<select class='state'><option value='off'>Off</option><option value='on'>On</option></select>";
    var txt = "";
    $.each(pin_data, function(idx, data){
      
      if(idx % 2 == 0){
        txt += '<tr><td>'+data.num+'</td><td>'+data.name+'</td><td data-idx="'+idx+'">';
        if(data.wpi_num != -1){
          txt += direction + '</td><td data-idx="'+idx+'">' + state;
        }else{
          txt += '</td><td>';
        }
        txt += '</td><td style="width:30px">';
        if(idx == 0){
          txt += "<i class='fa fa-square-o'></i>";
        }else{
          txt += "<i class='fa fa-dot-circle-o'></i>";
        }
        txt += "</td>"; 
      }else{
        txt += '<td style="width:30px"><i class="fa fa-dot-circle-o"></i></td><td  data-idx="'+idx+'">';
        if(data.wpi_num != -1){
          txt += state + '</td><td data-idx="'+idx+'">' + direction + '</td><td>';
        }else{
          txt += '</td><td></td><td>';
        }
        txt += data.name+'</td><td>'+data.num+'</td></tr>';
      }
    });

    $("table.pins-table").append(txt);
    
    $("select.direction").change(function(){
      var data = {};
      data.message = "set_direction";
      data.idx = parseInt($(this).parent().attr("data-idx"));
      data.direction = $(this).val();
      // console.log(data);
      PiTester.sendMessage(data);
    });

    $("select.state").change(function(){
      var data = {};
      data.message = "set_state";
      data.idx = parseInt($(this).parent().attr("data-idx"));
      data.state = $(this).val();
      // console.log(data);
      PiTester.sendMessage(data);
    });
  },

}