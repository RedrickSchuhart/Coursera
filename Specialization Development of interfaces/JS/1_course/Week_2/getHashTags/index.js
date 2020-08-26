/**
 * @param {String} tweet
 * @returns {String[]}
 */
module.exports = function (tweet) {
	words = tweet.split(' ');
	hashtags = [];
	for(i=0;i<words.length;i++) {
		if(words[i][0]=='#') {
			hashtags.push(words[i].slice(1,words[i].length));
		}
	}
	return hashtags;
};
