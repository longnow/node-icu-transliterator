let native = require('bindings')('node-icu-transliterator');

module.exports = function(rules, dir) {
    if (dir === undefined) dir = true;
    return new native.Transliterator(rules, dir);
}
