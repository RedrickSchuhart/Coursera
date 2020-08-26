module.exports = {
	events: {},
    /**
     * @param {String} event
     * @param {Object} subscriber
     * @param {Function} handler
     */
	on: function (event, subscriber, handler) {
		if(!this.events.hasOwnProperty(event))
			this.events[event]=[];
		this.events[event].push({
			subscriber_: subscriber,
			handler_: handler
		});
		return this;
	},

    /**
     * @param {String} event
     * @param {Object} subscriber
     */
	off: function (event, subscriber) {
		if(!this.events.hasOwnProperty(event))
			return this;
		i=0;
		for(i; i<this.events[event].length;) {
			mass = this.events[event];
			if(mass[i].subscriber_==subscriber){
				mass.splice(i, 1);
			} else {
				i++;
			}
		}
		return this;
	},

    /**
     * @param {String} event
     */
	emit: function (event) {
		if(!this.events.hasOwnProperty(event))
			return this;
		for(i=0; i<this.events[event].length; i++) {
			this.events[event][i].handler_.call(this.events[event][i].subscriber_);
		}
		return this;
	}
};
