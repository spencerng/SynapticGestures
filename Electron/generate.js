var $ = require('jquery');

var all_gestures;

var current_type;
var current_motion;
var current_action;

function listActions(){
	actions = ["Copy", "Cut", "Paste", "Left Click", "Right Click", 
	"Middle Click","Scroll Up", "Scroll Down", "Back", "Forward", "Switch Window", 
	"Scroll Left", "Scroll Right", "Change Tab", "Start Menu", "Show Desktop",
	"Print Screen"];
	var spacer =  document.createElement("div");
	spacer.className = 'spacer';
	var actionDiv = document.getElementById("action");
	actionDiv.appendChild(spacer);
	

	for(var i = 1; i <= 5; i++){
		var column = document.createElement("div");
		column.className = "column";
		column.id = "column" + i;
		actionDiv.appendChild(column);
	}
	var colNum = 1;

	for(var i = 0; i < actions.length; i++){
		var action = document.createElement("div");
		action.className= "gridobj";
		action.id=actions[i];
		while((action.id.replace(' ', '_')!==action.id))
			action.id = action.id.replace(' ', '_');
		
		action.innerHTML = actions[i];
		document.getElementById("column"+colNum).appendChild(action);
		action.onclick = function(){set_action(this.id);};
		if(++colNum==6)
			colNum = 1;

	}
	actionDiv.appendChild(spacer);
}

function reset_storage() {
	all_gestures = {
		"finger1": {
			"tap": "none",
			"pan": "none",
			"up": "none",
			"down": "none",
			"left": "none",
			"right": "none"
		},
		"finger2": {
			"tap": "none",
			"pan": "none",
			"up": "none",
			"down": "none",
			"left": "none",
			"right": "none"
		},
		"finger3": {
			"tap": "none",
			"pan": "none",
			"up": "none",
			"down": "none",
			"left": "none",
			"right": "none"
		}
	};
	localStorage.setItem("all_gestures", JSON.stringify(all_gestures));
}

$(document).ready(function() {
	if (localStorage.getItem("all_gestures") === null) {
		reset_storage();
		console.log("successfully stored");
	} else {
		all_gestures = JSON.parse(localStorage.getItem("all_gestures"));
		console.log("successfully retrieved");
	}
	listActions();
});

function set_type(type) {
	current_type = type;
	$("#" + type).removeClass("inactive_select");
	$("#type .selectobj:not(#" + type + ")").addClass("inactive_select");
}

function set_motion(motion) {
	current_motion = motion;
	$("#" + motion).removeClass("inactive_select");
	$("#motion .selectobj:not(#" + motion + ")").addClass("inactive_select");
}

function set_action(action) {
	current_action = action;
	$("#" + action).removeClass("inactive_select");
	$("#action .gridobj:not(#" + action + ")").addClass("inactive_select");
}

function generateAHK() {
	var fs = require('fs');
	var script = 'hello world'
	fs.writeFileSync('test.txt', script, 'utf-8');
	return null;
}

function apply() {
	all_gestures[current_type][current_motion] = current_action;
	localStorage.setItem("all_gestures", JSON.stringify(all_gestures));
	$("div").removeClass("inactive_select");
	console.log(all_gestures);
	generateAHK();
}

function reset() {
	reset_storage();
	$("div").removeClass("inactive_select");
}