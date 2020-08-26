/**
 * @param {String} date
 * @returns {Object}
 */
module.exports = function (newDate) {
	var time = new Date(newDate);
	Object.defineProperty(time, 'value', {
		value: createStr(time),
		writable: true
	});
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
			case "hours":
				time.setHours(time.getHours()+k*n);
			break;
			case "minutes":
				time.setMinutes(time.getMinutes()+k*n);
			break;
			default:
				throw new TypeError('Передано неверное значение');
			break;
			}
			this.value = createStr(this);
			return this;
		},
		writable: true,
		enumerable: false,
		configurable: true
	});
	Object.defineProperty(time, 'add', {
		value: function(n, type) {
			return this.op(1, n, type);
		}
	});
	Object.defineProperty(time, 'subtract', {
		value: function(n, type) {
			return this.op(-1, n, type);
		}
	});
	return time;
};

function createStr(date) {
	str = ''+date.getFullYear();
	str+='-';
	if(date.getMonth()<9)
		str+='0';
	str+=(date.getMonth()+1);
	str+='-';
	if(date.getDate()<10)
		str+='0';
	str+=date.getDate();
	str+=' ';
	if(date.getHours()<10)
		str+='0';
	str+=date.getHours()
	str+=':';
	if(date.getMinutes()<10)
		str+='0';
	str+=date.getMinutes()
	return str;
}
