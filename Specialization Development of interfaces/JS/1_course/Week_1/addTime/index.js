/**
 * @param {Number} hours
 * @param {Number} minutes
 * @param {Number} interval
 * @returns {String}
 */
module.exports = function (hours, minutes, interval) {
	minutes = minutes + interval;
	hours = (hours + (minutes-minutes%60)/60)%24;
	minutes = minutes%60;
	str="";
	if(hours<10) {
		str = "0";
	}
	str = str + hours + ":";
	if(minutes<10) {
		str = str + "0";
	}
	str = str + minutes;
	return str
};
