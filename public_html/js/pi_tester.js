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
      send.data.push(e.is(':checked'));
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
    })
  },

  socketOnMessage: function(ev){
    // console.log("GOT WS DATA");
    console.log("WS response: "+ev.data);
    // console.log(ev);

    var data = $.parseJSON(ev.data);
    // if(data.name == "get_buttons"){
    //   PiTester.handleGetButtonsResponses(data.data);
    // }
    
  },

  socketOnOpen: function(ev){
    //ask server for switch/lamp/coil information
    // PiTester.sendMessage({message: "get_buttons"});

    // PiTester.sendMessage({message: "get_lamps"});

    // PiTester.sendMessage({message: "get_coils"});

    // PiTester.sendMessage({message: "get_game_state"});

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

  handleGetButtonsResponses: function(button_data){
  },

}