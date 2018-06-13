let native = require('bindings')('node-icu-transliterator');

let self = module.exports = function(rules, dir) {
    if (dir === undefined) dir = self.FORWARD;
    return new native.Transliterator(rules, dir);
}

self.FORWARD = true;
self.REVERSE = false;
