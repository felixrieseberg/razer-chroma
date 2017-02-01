var Chroma = require('./');
var init = Chroma.InitChroma();


var current_col=0;
var grow=true;
var interval;
var customGrid = [];

for(var r=0; r<6; r++){
	customGrid[r]=[];
	for(var c=0; c<22; c++){
		customGrid[r][c]={
					Red: 0,
					Green: 0,
					Blue: 0
		};
	}
}

console.log(init)

if(init){
	console.log("Successfully initialized.");


	interval = setInterval(function(){

		var color = {
					Red: current_col,
					Green: 0,
					Blue: 0
		};

		for(var r=0; r<6; r++){
			for(var c=0; c<22; c++){
				customGrid[r][c]=color;
			}
		}

		Chroma.Keyboard.SetCustom(customGrid);

		if(grow) current_col++;
		else current_col--;
		if(current_col>255){
			current_col=255;
			grow=false;
		}
		if(current_col<0){
			current_col=0;
			grow=true;
		}
	},10);

	setTimeout(function(){
		clearInterval(interval);
		console.log(Chroma.UnInitChroma());
		console.log("Closing");
	},30000);
}
else console.log("Couldn't initalize SDK");

