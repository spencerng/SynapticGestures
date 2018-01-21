var $ = require("jquery");

var all_gestures;

var current_type;
var current_motion;
var current_action;

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