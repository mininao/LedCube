var SerialPort = require("serialport").SerialPort


var Cube = function(var serialPath, var fps, var debug) {
	
	this.serialPath = serialPath;
	this.fps = fps;
	this.debug = debug;
	
	this.leds = [[[]]];
	
	this.rate = 1000 / this.fps;
	
	this.sp = new SerialPort(this.serialPath, {
		baudrate: 57600,
		// defaults for Arduino serial communication
		dataBits: 8,
		parity: 'none',
		stopBits: 1,
		flowControl: false
	});
	
	if (debug) {
			this.sp.on("open", function () {
				console.log('Connection open');
			});
			this.sp.on("data", function (data) {
				console.log("\t" + data);
			});
	}	
}
