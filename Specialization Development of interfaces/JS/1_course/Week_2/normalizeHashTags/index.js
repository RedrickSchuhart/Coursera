/**
 * @param {String[]} hashtags
 * @returns {String}
 */
module.exports = function (hashtags) {
	for(i=0;i<hashtags.length;i=i) {
		hashtags[i] = hashtags[i].toLowerCase();
		j=0;
		for(j;j<i;j++) {
			if(hashtags[i]==hashtags[j]) {
				hashtags.splice(i, 1);
				break;
			}
		}
		if(j==i) {
			i++;
		}
	} 
	return hashtags.join(', ')
};
