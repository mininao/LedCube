var util = require('util');

module.exports.l = function(object){
  console.log(util.inspect(object,{colors:true}))
}

module.exports.cls = function() {
  process.stdout.write('\033c'); // Clear the console
}