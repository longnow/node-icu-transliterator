let native = require('bindings')('node-icu-transliterator');

function RBT(rules, dir) {
    if (rules === undefined) throw 'missing rules parameter';
    if (dir === undefined) dir = RBT.FORWARD;
    return new native.RBT(rules, dir);
}
RBT.FORWARD = true;
RBT.REVERSE = false;

function RBNF(rules) {
    if (rules === undefined) throw 'missing rules parameter';
    return new native.RBNF(rules);
}

exports.RBT = RBT;
exports.RBNF = RBNF;
