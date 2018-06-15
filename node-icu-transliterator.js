let native = require('bindings')('node-icu-transliterator');

let RBT = function RBT(id, dir) {
  if (id === undefined) throw 'missing id parameter';
  if (dir === undefined) dir = RBT.FORWARD;
  return new native.RBT(1, id, dir);
}

RBT.fromRules = function(rules, dir) {
  if (rules === undefined) throw 'missing rules parameter';
  if (dir === undefined) dir = RBT.FORWARD;
  return new native.RBT(2, rules, dir);
}

RBT.register = function(id, rules) {
  if (id === undefined) throw 'missing id parameter';
  if (rules === undefined) throw 'missing rules parameter';
  native.RBT.register(id, rules);
}

RBT.FORWARD = true;
RBT.REVERSE = false;

let RBNF = function RBNF(rules) {
  if (rules === undefined) throw 'missing rules parameter';
  return new native.RBNF(rules);
}

exports.RBT = RBT;
exports.RBNF = RBNF;
