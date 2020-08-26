/**
 * @param {Array} collection
 * @params {Function[]} – Функции для запроса
 * @returns {Array}
 */
function query(collection) {
	new_collection=collection;
	colums = Object.keys(collection[0]);
	for(var i = 1; i < arguments.length; i++) {
		if(typeof arguments[i]=='object') {
			new_colums=[];
			for(j1=0; j1<colums.length; j1++)
				for(j2=0; j2<arguments[i].length; j2++)
					if(arguments[i][j2]==colums[j1]) {
						new_colums.push(colums[j1]);
						break;
					}
			colums=new_colums;
		} else {
			new_collection = arguments[i](new_collection);
		}
	}
	result=[];
	for(var i = 0; i < new_collection.length; i++) {
		obj={};
		for(var j = 0; j < colums.length; j++) {
			obj[colums[j]]=new_collection[i][colums[j]];
		}
		result.push(obj);
	}
	return result;
}

/**
 * @params {String[]}
 */
function select() {
	arr=[].slice.call(arguments);;
	return arr;
}

/**
 * @param {String} property – Свойство для фильтрации
 * @param {Array} values – Массив разрешённых значений
 */
function filterIn(property, values) {
	return function filterIn(collection) {
		new_collection = [];
        	for(i=0; i<collection.length; i++) {
			for(j=0; j<values.length; j++) {
				if(collection[i][property]==values[j]) 	{	
					new_collection.push(collection[i]);
					break;
				}
			}
		}
        
        	return new_collection;
    	}
}

module.exports = {
    query: query,
    select: select,
    filterIn: filterIn
};
