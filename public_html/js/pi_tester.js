PiTester = {
  websocket: null,
  startup: function(){
    PiTester.websocket = new WebSocket("ws://"+location.host+"/ws");
    PiTester.websocket.onopen = PiTester.socketOnOpen;
    PiTester.websocket.onmessage = PiTester.socketOnMessage;
    PiTester.websocket.onclose = function(ev) {console.log(ev);}

    // $("select.game_state").change(function(){
    //   var data = {
    //     message: "set_game_state", 
    //     value: parseInt($(this).val())
    //   };
    //   PiTester.sendMessage(data);

    });
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