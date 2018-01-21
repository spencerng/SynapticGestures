var $ = require('jquery');

var all_gestures;
var fs = require('fs');
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
	generateAHK();	
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

function getModifyKey(finger){
	if(finger==2)
		return '+'
	else return '^'
}

function getActionAHK(action){
	if(action==="Copy")
		return 'Send, ^c'
	if(action==="Cut")
		return 'Send, ^x'
	if(action ==="Paste")
		return 'Send, ^v'
	if(action==="Left_Click")
		return 'Click'
	if(action==="Right_Click")
		return  'Click, Right'
	if(action==="Middle_Click")
		return 'Click, middle'
	if(action==="Scroll_Up")
		return 'SendInput, {WheelUp}'
	if(action=== "Scroll_Down")
		return 'SendInput, {WheelDown}'
	if(action=== "Back")
		return 'SendInput, {Browser_Back}'
	if(action=== "Forward")
		return 'SendInput, {Browser_Forward}'
	if(action==="Switch_Window")
		return 'Send, !{Tab}'
	if(action==="Scroll_Left")
		return 'Send, {WheelLeft}'
	if(action=== "Scroll_Right")
		return 'Send, {WheelRight}'
	if(action=== "Change_Tab")
		return 'Send, ^{Tab}'
	if(action=== "Start_Menu")
		return 'Send, #'
	if(action=== "Show_Desktop")
		return 'Send, #d'
	if(action==="Print_Screen")
		return 'Send, {PrintScreen}'
}

function generateAHK() {
	
	var script = '#SingleInstance Force\n'

	for(var i = 2; i <4; i++){
		if(all_gestures["finger"+i]["left"]!=="none"){
			if(i==2)
				script+="+Left::"+getActionAHK(all_gestures["finger"+i]["left"])+'\n\n'
			else script+="^Left::"+getActionAHK(all_gestures["finger"+i]["left"])+'\n\n'
		}
		if(all_gestures["finger"+i]["right"]!=="none"){
			if(i==2)
				script+="+Right::"+getActionAHK(all_gestures["finger"+i]["right"])+'\n\n'
			script+="^Right::"+getActionAHK(all_gestures["finger"+i]["right"])+'\n\n'
		}
		if(all_gestures["finger"+i]["up"]!=="none"){
			if(i==2)
				script+="+Up::"+getActionAHK(all_gestures["finger"+i]["up"])+'\n\n'
			else "^Up::"+getActionAHK(all_gestures["finger"+i]["up"])+'\n\n'
		}
		if(all_gestures["finger"+i]["down"]!=="none"){
			if(i==2)
				script+="+Down::"+getActionAHK(all_gestures["finger"+i]["down"])+'\n\n'
			script+="^Down::"+getActionAHK(all_gestures["finger"+i]["down"])+'\n\n'
		}
		if(all_gestures["finger"+i]["tap"]!=="none"){
			if(i==2)
				script+="RButton::"+getActionAHK(all_gestures["finger"+i]["tap"])+'\n\n'
			else script+="MButton::"+getActionAHK(all_gestures["finger"+i]["tap"])+'\n\n'
		}
	}
	fs.writeFileSync('script.ahk', script, 'utf-8');
	var child = require('child_process').execFile;
	var executablePath = "C:\\Program Files\\AutoHotkey\\AutoHotkey.exe";
	var parameters = ["script.ahk"];

	child(executablePath, parameters, function(err, data) {
    	 console.log(err)
     	console.log(data.toString());
	});
	return null;
}

function apply() {
	all_gestures[current_type][current_motion] = current_action;
	localStorage.setItem("all_gestures", JSON.stringify(all_gestures));
	$("div").removeClass("inactive_select");
	console.log(all_gestures);

	var macroDiv = document.getElementById("macro_div");
	var macroDisplay = document.createElement("div");
	macroDisplay.className = 'macro';
	var innerHTML = ''
	if(current_type === 'finger2')
		innerHTML += '2 finger ';
	else innerHTML += '3 finger ';
	if(current_motion!=='tap')
		innerHTML+=' swipe ';
	innerHTML+=current_motion+': '+current_action.replace('_', ' ')
	macroDisplay.innerHTML = innerHTML;
	macroDiv.appendChild(macroDisplay);
	generateAHK();
}

function reset() {
	reset_storage();
	$("div").removeClass("inactive_select");
	fs.writeFileSync('script.ahk', '#SingleInstance Force\n', 'utf-8');
	var macroDiv = document.getElementById("macro_div");
	while(macroDiv.firstChild){
		macroDiv.removeChild(macroDiv.firstChild);
	}
}