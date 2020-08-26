// Телефонная книга
var phoneBook = {};

/**
 * @param {String} command
 * @returns {*} - результат зависит от команды
 */
module.exports = function (command) {
	words = command.split(' ');
	switch (words[0]) {
	case "ADD":
		name = words[1].slice(0,words[1].length);
		if (!phoneBook.hasOwnProperty(name)) {
			phoneBook[name]=[];
		}
		words=words[2].split(',');
		for(i=0; i<words.length; i++) {
			for(j=0;j<phoneBook[name].length;j++) {
				if(words[i]==phoneBook[name][j]) {
					break;
				}
			}
			if(j==phoneBook[name].length) {
				phoneBook[name].push(words[i]);
			}
		}
		return null;
	break;
	case "REMOVE_PHONE":
		keys = Object.keys(phoneBook);
		for (i = 0; i < keys.length; i++) {
			name = keys[i];
			for(j=0; j<phoneBook[name].length; j++) {
				if(phoneBook[name][j]==words[1]) {
					phoneBook[name].splice(j,1);
					return true;
					j--;
				}
			}
		}
		return false;
	break;	
	case "SHOW":
		results = [];
		keys = Object.keys(phoneBook);
		for (i = 0; i < keys.length; i++) {
			name = keys[i];
			if(phoneBook[name].length>0) {
				result=name+': '+phoneBook[name].join(', ');
				results.push(result);
			}
		}
		return results.sort();
	break;
	default:
	}
	return null;
};
























	
	Object.defineProperty(time, 'op', {
		value: function(k, n, type) {
			if(n<0)
				throw new TypeError('Передано неверное число');
			switch (type) {
			case "years":
				time.setFullYear(time.getFullYear()+k*n);
			break;
			case "months":
				time.setMonth(time.getMonth()+k*n);
			break;
			case "days":
				time.setDate(time.getDate()+k*n);
			break;
			case "hours ":
				time.setHours(time.getHours()+k*n);
			break;
			case "minutes":
				time.setMinutes(time.getMinutes()+k*n);
			break;
			default:
				throw new TypeError('Передано неверное значение');
			break;
			return this;
		},
		writable: true,
		enumerable: false,
		configurable: true
	});
