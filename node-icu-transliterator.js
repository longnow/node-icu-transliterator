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

let RBNF = function RBNF(language, tag) {
  if (language === undefined) throw 'missing language parameter';
  if (tag === undefined) tag = RBNF.SPELLOUT;
  return new native.RBNF(language, tag);
}

RBNF.fromRules = function(rules) {
  if (rules === undefined) throw 'missing rules parameter';
  return new native.RBNF(rules);
}

RBNF.SPELLOUT = 0;
RBNF.ORDINAL = 1;
RBNF.DURATION = 2;
RBNF.NUMBERING_SYSTEM = 3;

exports.RBT = RBT;
exports.RBNF = RBNF;
