var handler = require('../lib/komachanhandler');
var komaHandler = new handler();

komaHandler.start();
komaHandler.finish(function(mess){
  console.log(mess);
  process.exit();
});

process.on('exit', function(){
  komaHandler.end();
});
